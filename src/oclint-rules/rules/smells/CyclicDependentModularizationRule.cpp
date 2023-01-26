#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <regex>
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include "oclint/util/Graph.h"
#include "oclint/util/Vertex.h"
#include "oclint/util/Edge.h"
#include "oclint/util/Thresholds.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class CyclicDependentModularizationRule : public AbstractASTVisitorRule<CyclicDependentModularizationRule>
{
private:
    int _threshold;
    list<string> _allClasses;
    Graph graph;


public:
    virtual const string name() const override
    {
        return "cyclic dependent modularization";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Design Smell";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.6";
    }

    virtual const std::string description() const override
    {
        return "Description...";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class Foo
    {
    public:
        int x;
        float y;

    }
        )rst";
    }

    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        thresholdMapping["MODULARIZATION_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("CYCLIC_DEPENDENT_MODULARIZATION", 1);
        _allClasses = getClassesList();
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        if (hasCyclicDependentModularization(decl)){
            string description = "C++ class has CyclicDependent Modularization.";
            addViolation(decl, this, description);
        }

        return true;
    }


    bool hasCyclicDependentModularization(CXXRecordDecl *decl){
        string className = decl->getNameAsString();
        if (!isAbstract(className)){
            return false;
        }
        initializeGraph();
        Vertex *thisVertex = getVertex(className);
        if (thisVertex == NULL ){
            cout << "Something wrong.." << endl;
        }
        (this->graph).computeStronglyConnectedComponents();
        list<list<Vertex*>> stronglyConnectedComponents = (this->graph).getStronglyConnectedComponents();
        int i = 1;
        for (auto vertexList = stronglyConnectedComponents.begin() ; vertexList != stronglyConnectedComponents.end() ; vertexList++){
            for (auto vertex = (*vertexList).begin() ; vertex != (*vertexList).end() ; vertex++){
                if(isInVerticesList(*vertexList,thisVertex)){
                    for (auto vertex = (*vertexList).begin() ; vertex != (*vertexList).end() ; vertex++){
                        if (! (*vertex == thisVertex)){
                            if (isAbstract((*vertex)->getName())){
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    list<string> getClassesList(){
        list<string> classes;
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        string delimiter = ";";
        // Run over each line in Data
        while (getline(file, line)) {
            string token;
            size_t pos = line.find(delimiter);
            token = line.substr(0, pos);
            classes.push_back(token);
        }
        return classes;
    }


    string getParents(string child) {
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        string delimiter = ";";
        // Run over each line in Data
        while (getline(file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                if (i == 1 && token != child) {
                    break;
                }
                line.erase(0, pos + delimiter.length());
                if (i == 5) {
                    return token;
                }
                i++;
            }
        }
        return "";
    }

    int countStringInMethod (FunctionDecl *decl, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        Stmt *funcBody = decl->getBody();
        if (funcBody == 0){
            return false;
        }
        SourceRange range = funcBody->getSourceRange();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string text = get_source_text_raw(printable_range, *TheSourceMgr);
        string theRegex = regex_begin + str + regex_begin;
        if (regex_search(text , regex(theRegex))){
            regex re(theRegex);
            auto words_begin = std::sregex_iterator(text.begin(), text.end(), re);
            auto words_end = std::sregex_iterator();
            return distance(words_begin, words_end);
        } else return 0;

    }
    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}



    bool isInClassList(string str){
        for (auto stm = _allClasses.begin() ; stm != _allClasses.end() ; stm++){
            if (*stm == str){
                return true;
            }
        }
        return false;
    }
    int getNumOfFanIn(CXXRecordDecl *decl) {
        string methodName = decl->getNameAsString();
        string theRegexMethod = "^" + methodName + ":";
        string tempNum;
        int sum = 0;
        std::ifstream file;
        file.open("/tmp/NumOfFanIn");
        string line;
        int sumOfOuts = 0;
        string delimiter = ",";
        // Run over each line in Data
        while (getline(file, line)) {
            size_t pos = 0, pos1 = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                if (regex_search(token , regex(theRegexMethod))){
                    pos1 = token.find(":");
                    token.erase(0, pos1+1);
                    sum += stoi(token);
                }

            }
        }
        file.close();
        return sum;
    }

    bool isAbstract(string classToCheck){
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        string delimiter = ";";
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==1 && token != classToCheck) {
                    break;
                }
                if (i == 2){
                    if (token == "1"){
                        return true;
                    } else{
                        return false;
                    }
                }
                line.erase(0, pos+delimiter.length());
                i++;
            }

        }
        return false;
    }

    void initializeGraph(){
        initializeVertices();
        initializeEdges();

    }

    void initializeVertices(){
        for (auto c = (this->_allClasses).begin() ; c != (this->_allClasses).end() ; c++ ) {
            Vertex *newVertex= new Vertex(*c, VerType::Record);
            (this->graph).addVertex(newVertex);
        }
    }

    void initializeEdges(){
        string tempNum;
        std::ifstream file;
        file.open("/tmp/NumOfFanIn");
        string line;
        string delimiter = ";";
        string delimiter2 = ":";
        for (auto c = (this->_allClasses).begin() ; c != (this->_allClasses).end() ; c++ ){
            // Run over each line in Data
            getline(file, line);
            size_t pos = 0;
            size_t posIn = 0;
            string token;
            string tokenClass;
            string tokenNum;

            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                posIn = token.find(delimiter2);
                tokenClass = token.substr(0, posIn);
                tokenNum = token.erase(0, posIn + delimiter2.length());
                if (tokenNum != "0"){
                    Vertex *fromVer = getVertex(*c);
                    Vertex *toVer = getVertex(tokenClass);
                    Edge *newEdge = new Edge(fromVer, toVer);
                    (this->graph).addEdge(newEdge);
                }

            }
        }
        file.close();
    }



    Vertex* getVertex(string name){
        list<Vertex*> allVertices= (this->graph).getAllVertices();
        for (auto v = allVertices.begin() ; v != allVertices.end() ; v++ ){
            if((*v)->isSameVertex(name,VerType::Record)){
                return *v;
            }
        }
        return NULL;
    }

    bool isInVerticesList (list<Vertex*> verticesList, Vertex *vertex){
        for (auto it = verticesList.begin(); it != verticesList.end(); it++) {
            if(**it == *vertex){
                return true;
            }
        }
        return false;
    }




};

static RuleSet rules(new CyclicDependentModularizationRule());

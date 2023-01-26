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

class HubLikeModularizationRule : public AbstractASTVisitorRule<HubLikeModularizationRule>
{
private:
    int _threshold;
    list<string> _allClasses;
    Graph graph;


public:
    virtual const string name() const override
    {
        return "hub like modularization";
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
        _threshold = RuleConfiguration::intForKey("HUB_LIKE_MODULARIZATION", 1);
        _allClasses = getClassesList();
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        if (hasHubLikeModularization(decl)){
            string description = "C++ class has Hub Like Modularization.";
            addViolation(decl, this, description);
        }

        return true;
    }

    bool hasHubLikeModularization(CXXRecordDecl *decl){
        int numOfFanOutMethods = 0;
        int numOfFanOutFields = 0;
        string temp;
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            for (auto c = _allClasses.begin() ; c != _allClasses.end() ; c++){
                if (countStringInMethod(*f,*c)>0)
                numOfFanOutMethods ++;
            }
        }
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            const char *typeCharClass = (((*f)->getTypeSourceInfo())->getType())->getTypeClassName();
            string typeClass = typeCharClass;
            if(typeClass == "Record") {
                string typeString = ((((*f)->getTypeSourceInfo())->getType())->getAsRecordDecl())->getNameAsString();
                for (auto classToCheck = _allClasses.begin() ; classToCheck != _allClasses.end() ; classToCheck++){
                    if (typeString == *classToCheck){
                        numOfFanOutFields ++;
                    }
                }
            }
        }
        int numOfFanOut = numOfFanOutFields + numOfFanOutMethods;
        int numOfFanIn = getNumOfFanIn(decl);
//        cout << "Fol the class: " << decl->getNameAsString() << ": in: " << numOfFanIn << ", out: " <<numOfFanOut << endl;
        if (numOfFanOut >= HUBLIKE_MODULARIZATION_LARGE_FANOUT &&  numOfFanIn>=HUBLIKE_MODULARIZATION_LARGE_FANIN){
            return true;
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

        string text_origin = get_source_text_raw(printable_range, *TheSourceMgr);
        string text = cleanCommentsFromCodeText(text_origin);
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

    string cleanCommentsFromCodeText(string origin){
        string delimiter1 = "//";
        string delimiter2 = "\n";
        string delimiter3 = "/*";
        string delimiter4 = "*/";
        size_t pos1 = 0;
        size_t pos2 = 0;
        size_t pos3 = 0;
        size_t pos4 = 0;
        while ((pos1 = origin.find(delimiter1)) != string::npos){
            pos2 = origin.find(delimiter2,pos1);
            origin.erase(pos1,pos2-pos1);
        }
        while ((pos3 = origin.find(delimiter3)) != string::npos){
            pos4 = origin.find(delimiter4,pos3);
            origin.erase(pos3,pos4-pos3);
        }
        return origin;
    }

    int getNumOfFanIn(CXXRecordDecl *decl) {
        string className = decl->getNameAsString();
        string theRegexClass = "^" + className + ":";
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
                if (regex_search(token, regex(theRegexClass))) {
                    pos1 = token.find(":");
                    token.erase(0, pos1 + 1);
                    sum += stoi(token);
                }
                line.erase(0, pos + delimiter.length());
            }
        }
        file.close();
        return sum;
    }




};

static RuleSet rules(new HubLikeModularizationRule());

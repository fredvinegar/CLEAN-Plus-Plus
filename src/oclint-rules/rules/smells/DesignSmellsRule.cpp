#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <regex>
#include <list>
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include "oclint/util/Graph.h"
#include "oclint/util/Vertex.h"
#include "oclint/util/Edge.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class DesignSmellsRule : public AbstractASTVisitorRule<DesignSmellsRule>
{
private:
    int _threshold;
    Graph graph;
    list<string> classFields;
    list<string> classMethods;


public:
    virtual const string name() const override
    {
        return "design smells";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "smells";
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
        thresholdMapping["DESIGN_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
            _threshold = RuleConfiguration::intForKey("DESIGN_SMELLS", 1);

    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        cout << "Inside DesignSmells!" <<endl;

        this->classMethods = getMethodsList(decl);
        this->classFields = getFieldsList((decl));

        if (hasImperativeAbstraction(decl)){
            string description = "C++ class has Imperative Abstraction.";
            addViolation(decl, this, description);
        }
        if (hasMultifacetedAbstraction(decl)){
            string description = "C++ class has Multifaceted Abstraction.";
            addViolation(decl, this, description);
        }
        if (hasUnnecessaryAbstraction(decl)){
            string description = "C++ class has Unnecessary Abstraction.";
            addViolation(decl, this, description);
        }
        if (hasUnutilizedAbstraction(decl)){
            string description = "C++ class has Unutilized Abstraction.";
            addViolation(decl, this, description);
        }
        return true;
    }

    bool hasImperativeAbstraction(CXXRecordDecl *decl){
        //// change the threshold:
        int threshold = 50;
        int numOfPublicMethods = 0;
        for(auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            if ((*f)->getAccess() == clang::AS_public) {
                numOfPublicMethods++;
            }
        }
        if (numOfPublicMethods != 1) {
            return false;
        }
        for(auto f = decl->method_begin() ; f != decl->method_end() ; f++ ){
            if ((*f)->getAccess() == clang::AS_public){
                Stmt *stmt = f->getBody();
                int length = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
                if (length > threshold){
                    return true;
                }
            }
        }
        return false;
    }

    bool hasMultifacetedAbstraction(CXXRecordDecl *decl){
        if (getLCOM(decl) >= 0.8 && (this->classMethods).size() >= 7 && (this->classFields).size() >= 7){
            return true;
        }
        return false;
    }

    bool hasUnnecessaryAbstraction(CXXRecordDecl *decl){
        //// change the threshold:
        int threshold = 5;

        int numOfMethods = 0 , numOfFields = 0;
        for(auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            numOfMethods ++;
        }
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            numOfFields ++;
        }
        if (numOfMethods == 0 && numOfFields <= threshold){
            return true;
        }

        return false;
    }

    bool hasUnutilizedAbstraction(CXXRecordDecl *decl){
        list<string> parentList = getParentsList(decl);
        string className = decl->getNameAsString();

        if (!parentList.empty()){
            if (getNumOfFanIn(className) == 0){
                return true;
            } else{
                for (auto parent = parentList.begin() ; parent != parentList.end() ; parent++){
                    if (getNumOfFanIn(*parent) == 0 ){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    list<string> getParentsList(CXXRecordDecl *decl){
        list<string> parentsList;
        string className = decl->getNameAsString();
        std::ifstream file;
        file.open("/robo/oclint-repo/oclint-scripts/Data");
        string line;
        string strOfParents;
        string delimiter = ";";
        // Run over each line in Data
        while (getline(file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                if (i == 1 && token != className) {
                    break;
                }
                line.erase(0, pos + delimiter.length());
                if (i == 5) {
                    strOfParents = token;
                    break;
                }
                i++;
            }
        }
        if (strOfParents == ""){
            return parentsList;
        }
        string newDel = " ";
        size_t pos = 0;
        string token;
        while ((pos = strOfParents.find(newDel)) != string::npos) {
            token = strOfParents.substr(0, pos);
            parentsList.push_back(token);
            strOfParents.erase(0, pos + newDel.length());
        }parentsList.push_back(strOfParents);
        return parentsList;
    }

    int getNumOfFanIn(string className) {
        string tempNum;
        int sum = 0;
        std::ifstream file;
        file.open("/robo/oclint-repo/oclint-scripts/NumOfFanIn");
        string line;
        int sumOfOuts = 0;
        string delimiter = ";";
        // Run over each line in Data
        while (getline(file, line)) {
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                if (token.find(className) != string::npos){
                    tempNum = token.substr(className.length()+1);
                    sum += stoi(tempNum);
                }

            }
        }
        file.close();
        return sum;
    }
    list<string> getMethodsList(CXXRecordDecl *decl){
        list<string> methodsList;
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ) {
            methodsList.push_back((*method)->getNameAsString());
        }
        return methodsList;
    }

    list<string> getFieldsList(CXXRecordDecl *decl){
        list<string> fieldsList;
        for (auto field = decl->field_begin() ; field != decl->field_end() ; field++ ){
            fieldsList.push_back((*field)->getNameAsString());
        }
        return fieldsList;
    }

    bool isNotLcomComputable(CXXRecordDecl *decl){
        list<string> fieldsList = getFieldsList(decl);
        list<string> methodsList = getMethodsList(decl);
        if (decl->isAbstract() || fieldsList.empty() || methodsList.empty()){
            return true;
        }
        return false;
    }

    float getLCOM(CXXRecordDecl *decl){
        if (isNotLcomComputable(decl)){
            return -1.0;
        }else{
            initializeGraph(decl);
            return computeLCOM();
        }
    }

    void initializeGraph(CXXRecordDecl *decl){
        initializeVertices(decl);
        initializeEdges(decl);
    }

    void initializeVertices(CXXRecordDecl *decl){
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ) {
            Vertex *newVertex= new Vertex((*method)->getNameAsString(), VerType::Method);
            (this->graph).addVertex(newVertex);
        }
        for (auto field = decl->field_begin() ; field != decl->field_end() ; field++ ) {
            Vertex *newVertex= new Vertex((*field)->getNameAsString(), VerType::Field);
            (this->graph).addVertex(newVertex);
        }
    }

    void initializeEdges(CXXRecordDecl *decl){
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            addAdjacentFields(*method);
            addAdjacentMethods(*method);
        }
    }

    float computeLCOM(){
        (this->graph).computeConnectedComponents();
        list<list<Vertex*>> nonSingleElementFieldComponents = getNonSingleElementFieldComponents();
        if(nonSingleElementFieldComponents.size() > 1){
            float ans = static_cast< float >(nonSingleElementFieldComponents.size()) / static_cast< float >((this->classMethods.size()));
            return static_cast< float >(nonSingleElementFieldComponents.size()) / static_cast< float >((this->classMethods.size()));
        }
        return 0.0;
    }

    list<list<Vertex*>> getNonSingleElementFieldComponents(){
        list<list<Vertex*>> cleanComponents;
        list<list<Vertex*>> connectedComponent = (this->graph).getConnectedComponents();
        int i =1;
        for (auto component = connectedComponent.begin() ; component != connectedComponent.end() ; component++ ){
            if ((*component).size() != 1 || ((*component).front())->getType() != Field){
                cleanComponents.push_back(*component);
            }
            i ++;
        }
        return cleanComponents;
    }

    list<string> getDirectFieldAccesses(FunctionDecl *method){
        list<string> methodFieldsAccess;
        for (auto field = (this->classFields).begin() ; field != (this->classFields).end() ; field++ ){
            if (hasStringInMethod(method,*field)){
                methodFieldsAccess.push_back(*field);
            }
        }
        return methodFieldsAccess;
    }

    list<string> getDirectMethodAccesses(FunctionDecl *method){
        list<string> methodMethodsAccess;
        for (auto m = (this->classMethods).begin() ; m != (this->classMethods).end() ; m++ ){
            if (hasStringInMethod(method,*m)){
                methodMethodsAccess.push_back(*m);
            }
        }
        return methodMethodsAccess;
    }

    Vertex* getVertex(string name, VerType type){
        list<Vertex*> allVertices= (this->graph).getAllVertices();
        for (auto v = allVertices.begin() ; v != allVertices.end() ; v++ ){
            if((*v)->isSameVertex(name,type)){
                return *v;
            }
        }
        return NULL;
    }

    void addAdjacentFields(FunctionDecl *method) {
        list<string> fieldList= getDirectFieldAccesses(method);
        for (auto f = fieldList.begin() ; f != fieldList.end() ; f++ ){
            Vertex *fieldVertex = getVertex(*f, Field);
            Vertex *methodVertex = getVertex(method->getNameAsString(), Method);
            Edge *newEdge = new Edge(methodVertex, fieldVertex);
            (this->graph).addEdge(newEdge);
        }
    }

    void addAdjacentMethods(FunctionDecl *method) {
        list<string> methodList= getDirectMethodAccesses(method);
        for (auto m = methodList.begin() ; m != methodList.end() ; m++ ){
            Vertex *methodCalledVertex = getVertex(*m, Method);
            Vertex *methodVertex = getVertex(method->getNameAsString(), Method);
            Edge *newEdge = new Edge(methodVertex, methodCalledVertex);
            (this->graph).addEdge(newEdge);
        }
    }


    bool hasStringInMethod (FunctionDecl *decl, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        Stmt *funcBody = decl->getBody();
        if (funcBody==0){
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
            return true;
        } else return false;

    }
    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}






};

static RuleSet rules(new DesignSmellsRule());

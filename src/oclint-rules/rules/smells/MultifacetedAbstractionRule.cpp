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
#include "oclint/util/Thresholds.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class MultifacetedAbstractionRule : public AbstractASTVisitorRule<MultifacetedAbstractionRule>
{
private:
    int _threshold;
    Graph graph;
    list<string> classFields;
    list<string> classMethods;


public:
    virtual const string name() const override
    {
        return "multifaceted abstraction";
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
        thresholdMapping["DESIGN_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("MULTIFACETED_ABSTRACTION", 1);

    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        this->graph = Graph();
        this->classMethods = getMethodsList(decl);
        this->classFields = getFieldsList((decl));
        if (hasMultifacetedAbstraction(decl)){
            string description = "C++ class has Multifaceted Abstraction.";
            addViolation(decl, this, description);
        }
        return true;
    }


    bool hasMultifacetedAbstraction(CXXRecordDecl *decl){
        float lcom = getLCOM(decl);
        if (lcom >= MULTIFACETED_ABSTRACTION_LARGE_LCOM && (this->classMethods).size() >= MULTIFACETED_ABSTRACTION_MANY_METHODS && (this->classFields).size() >= MULTIFACETED_ABSTRACTION_MANY_FIELDS){
            return true;
        }
        return false;
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
        bool isClass = decl->isClass();
        bool hasDefinition = decl->hasDefinition();
        list<string> fieldsList = getFieldsList(decl);
        list<string> methodsList = getMethodsList(decl);
        bool isAbs = false;
        if (isClass && hasDefinition){
            isAbs = decl->isAbstract();
        }
        if (isAbs || fieldsList.empty() || methodsList.empty()){
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
            if(!isInVerticesList((this->graph).getAllVertices(),newVertex)){
                (this->graph).addVertex(newVertex);
            }

        }
        for (auto field = decl->field_begin() ; field != decl->field_end() ; field++ ) {

            Vertex *newVertex= new Vertex((*field)->getNameAsString(), VerType::Field);
            if(!isInVerticesList((this->graph).getAllVertices(),newVertex)){
                (this->graph).addVertex(newVertex);
            }

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
        if(nonSingleElementFieldComponents.size() >= 1){
            return static_cast< float >(nonSingleElementFieldComponents.size()) / static_cast< float >((this->classMethods.size()));
        }
        return 0.00;
    }

    list<list<Vertex*>> getNonSingleElementFieldComponents(){
        list<list<Vertex*>> cleanComponents;
        list<list<Vertex*>> connectedComponent = (this->graph).getConnectedComponents();
        for (auto component = connectedComponent.begin() ; component != connectedComponent.end() ; component++ ){
            if ((*component).size() == 1 && ((*component).front())->getType() == VerType::Field){

            } else{
                for (auto c = component->begin() ; c != component->end() ; c++ ){
                }

                cleanComponents.push_back(*component);
            }
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
            Edge *newEdge1 = new Edge(methodVertex, fieldVertex);
            Edge *newEdge2 = new Edge(fieldVertex, methodVertex);
            (this->graph).addEdge(newEdge1);
            (this->graph).addEdge(newEdge2);
        }
    }

    void addAdjacentMethods(FunctionDecl *method) {
        list<string> methodList= getDirectMethodAccesses(method);
        for (auto m = methodList.begin() ; m != methodList.end() ; m++ ){
            Vertex *methodCalledVertex = getVertex(*m, Method);
            Vertex *methodVertex = getVertex(method->getNameAsString(), Method);
            Edge *newEdge1 = new Edge(methodVertex, methodCalledVertex);
            Edge *newEdge2 = new Edge(methodCalledVertex, methodVertex);
            (this->graph).addEdge(newEdge1);
            (this->graph).addEdge(newEdge2);
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

        string text_before = get_source_text_raw(printable_range, *TheSourceMgr);
        string text = cleanCommentsFromCodeText(text_before);
        string theRegex = regex_begin + str + regex_begin;
        if (regex_search(text , regex(theRegex))){
            return true;
        } else return false;

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

    bool isInVerticesList (list<Vertex*> verticesList, Vertex *vertex){
        for (auto it = verticesList.begin(); it != verticesList.end(); it++) {
            if(**it == *vertex){
                return true;
            }
        }
        return false;
    }



};

static RuleSet rules(new MultifacetedAbstractionRule());

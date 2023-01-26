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

class ImperativeAbstractionRule : public AbstractASTVisitorRule<ImperativeAbstractionRule>
{
private:
    int _threshold;
    Graph graph;
    list<string> classFields;
    list<string> classMethods;


public:
    virtual const string name() const override
    {
        return "imperative abstraction";
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
        _threshold = RuleConfiguration::intForKey("IMPERATIVE_ABSTRACTION", 1);

    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        this->classMethods = getMethodsList(decl);
        this->classFields = getFieldsList((decl));
        if (hasImperativeAbstraction(decl)){
            string description = "C++ class has Imperative Abstraction.";
            addViolation(decl, this, description);
        }
        return true;
    }

    bool hasImperativeAbstraction(CXXRecordDecl *decl){
//        cout << decl->getNameAsString() << endl;
        int threshold = IMPERATIVE_ABSTRACTION_LARGE_NUM_OF_LINES;
        int numOfPublicMethods = 0;
        for(auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            if ((*f)->getAccess() == clang::AS_public) {
                numOfPublicMethods++;
            }
        }
        if (numOfPublicMethods != 1) {
            return false;
        }
//        cout << 1 << endl;
        for(auto f = decl->method_begin() ; f != decl->method_end() ; f++ ){
            if ((*f)->getAccess() == clang::AS_public){
                Stmt *stmt = f->getBody();
                int length = 0;
                if (stmt != 0){
                    length = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
                }
                if (length > threshold){
                    return true;
                }
            }
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




};

static RuleSet rules(new ImperativeAbstractionRule());

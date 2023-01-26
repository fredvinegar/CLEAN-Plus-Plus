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

class BrokenModularizationRule : public AbstractASTVisitorRule<BrokenModularizationRule>
{
private:
    int _threshold;
    list<string> _allClasses;
    Graph graph;


public:
    virtual const string name() const override
    {
        return "broken modularization";
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
        _threshold = RuleConfiguration::intForKey("BROKEN_MODULARIZATION", 1);
        _allClasses = getClassesList();
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        if (hasBrokenModularization(decl)){
            string description = "C++ class has Broken Modularization.";
            addViolation(decl, this, description);
        }

        return true;
    }

    bool hasBrokenModularization(CXXRecordDecl *decl){
        int numOfMethods = 0;
        int numOfFields = 0;
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            numOfMethods++;

        }
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            numOfFields++;
        }
        if (numOfMethods==0 && numOfFields>BROKEN_MODULARIZATION_LARGE_FIELDS){
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


};

static RuleSet rules(new BrokenModularizationRule());

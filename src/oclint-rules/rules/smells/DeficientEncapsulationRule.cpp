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
#include "oclint/util/Thresholds.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class DeficientEncapsulationRule : public AbstractASTVisitorRule<DeficientEncapsulationRule>
{
private:
    int _threshold;


public:
    virtual const string name() const override
    {
        return "deficient encapsulation";
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
        thresholdMapping["ENCAPSULATION_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("DEFICIENT_ENCAPSULATION", 1);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        if (hasDeficientEncapsulation(decl)){
            string description = "C++ class has Deficient Encapsulation.";
            addViolation(decl, this, description);
        }


        return true;
    }

    bool hasDeficientEncapsulation(CXXRecordDecl *decl){
        clang::RecordDecl::field_iterator field = decl->field_begin();
        while (field != decl->field_end()) {
            if ((*field)->getAccess() == clang::AS_public) {
                return true;
            }
            field ++;
        }
        return false;
    }

};

static RuleSet rules(new DeficientEncapsulationRule());

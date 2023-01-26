#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace clang;
using namespace oclint;

class ClassDataShouldBePrivateRule : public AbstractASTVisitorRule<ClassDataShouldBePrivateRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "class data should be private";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Organic Class Smell";
    }

//#ifdef DOCGEN
//    virtual const std::string since() const override
//    {
//        return "0.6";
//    }
//
//    virtual const std::string description() const override
//    {
//        return "Description...";
//    }
//
//    virtual const std::string example() const override
//    {
//        return R"rst(
//.. code-block:: cpp
//
//    class Foo
//    {
//    public:
//        int x;
//        float y;
//
//    }
//        )rst";
//    }
//
//    virtual const std::map<std::string, std::string> thresholds() const override
//    {
//        std::map<std::string, std::string> thresholdMapping;
//        thresholdMapping["CLASS_DATA_SHOULD_BE_PRIVATE"] =
//            "One or more public fields.";
//        return thresholdMapping;
//    }
//#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("CLASS_DATA_SHOULD_BE_PRIVATE", 1);
    }
//    bool VisitFieldDecl (FieldDecl  *decl) {
//        if (decl->getAccess() == clang::AS_public) {
//            string description = "C++ class having at least one public field.";
//            addViolation(decl->getParent(), this, description);
//        }
//        return true;
//    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        clang::RecordDecl::field_iterator field = decl->field_begin();
        while (field != decl->field_end()) {
            if ((*field)->getAccess() == clang::AS_public) {
                string description = "C++ class having at least one public field.";
                addViolation(decl, this, description);
                break;
            }
            field ++;
        }
        return true;
    }
};

static RuleSet rules(new ClassDataShouldBePrivateRule());

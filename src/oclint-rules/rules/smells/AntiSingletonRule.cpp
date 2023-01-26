#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "oclint/metric/IsClassSingletonMetric.h"
#include "oclint/metric/ClassPublicFieldCountMetric.h"
#include "oclint/metric/ClassPublicAccessorCountMetric.h"
#include <iostream>

using namespace std;
using namespace clang;
using namespace oclint;

class SingletonFinderRule : public AbstractASTVisitorRule<SingletonFinderRule>
{
public:
    virtual const string name() const override
    {
        return "anti-singleton";
    }

    virtual int priority() const override
    {
        return 1;
    }

    virtual const string category() const override
    {
        return "Organic Class Smell";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "21.10";
    }

    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // TODO: modify the example for this rule.
    }
        )rst";
    }

    /* fill in the file name only when it does not match the rule identifier
    virtual const std::string fileName() const override
    {
        return "";
    }
    */

    /* add each threshold's key, description, and its default value to the map.
    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        return thresholdMapping;
    }
    */

    /* add additional document for the rule, like references, notes, etc.
    virtual const std::string additionalDocument() const override
    {
        return "";
    }
    */

    /* uncomment this method when the rule is enabled to be suppressed.
    virtual bool enableSuppress() const override
    {
        return true;
    }
    */
#endif

    virtual void setUp() override {}
    virtual void tearDown() override {}

    void applyOnClass() {

    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        if (decl->isClass() || decl->isStruct()) {
            bool isSingleton = (IsClassSingletonMetric{}).calculate(decl);
            if (isSingleton)
            {
                int publicFieldsCount = (ClassPublicFieldCountMetric{}).count(decl);
                int publicAccessorCount = (ClassPublicAccessorCountMetric{false}).count(decl);
                if (publicFieldsCount + publicAccessorCount > 1)
                {
                    addViolation(decl, this, "Class `" + decl->getName().str() + "` in an anti-singleton");
                }

//                std::cout << "Found singleton `" << decl->getQualifiedNameAsString() << "`";
//                std::cout << ", with " << publicFieldsCount << " public fields";
//                std::cout << ", and " << publicAccessorCount << " public accessors";
//                std::cout << "\n";
            }
        }
        return true;
    }
};

static RuleSet rules(new SingletonFinderRule());

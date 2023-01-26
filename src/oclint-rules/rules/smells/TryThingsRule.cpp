#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "oclint/metric/MethodMaxNestingMetric.h"


using namespace std;
using namespace clang;
using namespace oclint;

class TryThingsRule : public AbstractASTVisitorRule<TryThingsRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "try things";
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
        return "All classes having LOCs lower than the first quartile of the distribution of LOCs for all system’s classes.";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class Foo
    {
        void bar()
        {
            // 1001 lines of code
        }
    }
        )rst";
    }

    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        thresholdMapping["LAZY_CLASS"] =
            "The class size reporting threshold, default value is 1000.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl){
        int maxNesting = 0;
        for (auto fun = decl->method_begin() ; fun != decl->method_end() ; fun++ ){
            maxNesting = (MethodMaxNestingMetric{}).calculate(*fun);
            cout << maxNesting   << endl;
        }




        return true;
    }

};

static RuleSet rules(new TryThingsRule());

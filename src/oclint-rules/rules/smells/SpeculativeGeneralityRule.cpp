#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "oclint/util/Thresholds.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SpeculativeGeneralityRule : public AbstractASTVisitorRule<SpeculativeGeneralityRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "speculative generality";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Organic Class Smell";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.7";
    }

    virtual const std::string description() const override
    {
        return "A class declared as abstract having less than three children classes using its methods.";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class c
    {
        int a();
        int b();
        int c();
        // ...
        int l();
        int m();
        int n();
        // ...
        int x();
        int y();
        int z();
        int aa();
        int ab();
        int ac();
        int ad();
        int ae();
    };
        )rst";
    }

    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        thresholdMapping["SPECULATIVE_GENERALITY"] =
            "The reporting threshold for too many methods, default value is 3.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("SPECULATIVE_GENERALITY", SPECULATIVE_GENERALITY_MIN_CHILDREN);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        bool isClass = decl->isClass();
        bool hasDefinition = decl->hasDefinition();
        string name1 = " " + decl->getNameAsString();
        string name2 = ";" + decl->getNameAsString();
        bool isAbs = false;
        if (isClass && hasDefinition){
            isAbs = decl->isAbstract();
        }
        if (isAbs)
        {
            int numOfChildren = 0;
            std::ifstream file;
            file.open("/tmp/Data");
            string line;
            string delimiter = ";";
            // Run over each line in Data
            while (getline (file, line)) {
                size_t found1 = line.find(name1);
                size_t found2 = line.find(name2);
                if (found1 != string::npos || found2 != string::npos){
                    numOfChildren ++;
                    }
                }
            file.close();
            if (numOfChildren < _threshold){
                string description = "C++ abstract class with " + toString<int>(numOfChildren) +
                                     " children under the limit of " + toString<int>(_threshold);
                addViolation(decl, this, description);
            }

        }
        return true;
    }
};

static RuleSet rules(new SpeculativeGeneralityRule());

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

class LongParameterListRule : public AbstractASTVisitorRule<LongParameterListRule>
{
private:

public:
    virtual const string name() const override
    {
        return "long parameter list";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Implementation Smell";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.7";
    }

    virtual const std::string description() const override
    {
        return "A class with too many methods indicates it does too many things "
            "and is hard to read and understand. "
            "It usually contains complicated code, and should be refactored.";
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
        thresholdMapping["SWISS_ARMY_KNIFE"] =
            "The reporting threshold for too many methods, default value is 10.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {

    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        for (auto method = decl->method_begin(); method != decl->method_end(); method++) {
            string method_name = method->getNameAsString();
            int parameter_num = method->getNumParams();
            float threshold = getParamThreshold();
            if ((parameter_num > threshold && parameter_num > LONG_PARAMETER_THRESHOLD1) || parameter_num > LONG_PARAMETER_THRESHOLD2) {
                string description = method_name + ": method with " + toString<int>(parameter_num) +
                                     " parameters";
                addViolation(decl, this, description);
            }
        }
            return true;

    }

    float getParamThreshold(){
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        int sumOfMethods = 0;
        int sumOfParam = 0;
        string delimiter = ";";
        // Run over each line in Data
        while (getline (file, line)) {
            sumOfMethods ++;
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                line.erase(0, pos+delimiter.length());
                i++;
                if (i == 4){
                    sumOfParam += stoi(token);
                }
            }

        }
        file.close();
        // Calculate the threshold
        float  avg = 0.0;
        if (sumOfMethods > 0){
            avg = (static_cast< float >(sumOfParam) / static_cast< float >(sumOfMethods));
        }

        return avg;
    }
};

static RuleSet rules(new LongParameterListRule());

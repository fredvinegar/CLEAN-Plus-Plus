#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace clang;
using namespace oclint;

class SwissArmyKnifeRule : public AbstractASTVisitorRule<SwissArmyKnifeRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "swiss army knife";
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
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        int sumOfMethods = 0;
        int numOfAbstracts = 0;
        string delimiter = ";";
        vector<int> allMethodsNums;
        // Run over each line in Data
        while (getline (file, line)) {
            bool isAbstract = false;
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==2) {
                    isAbstract = (token == "1");
                    if (isAbstract == true) {
                        numOfAbstracts++;
                    }
                }

                line.erase(0, pos+delimiter.length());
                i++;
                if (i == 5 && isAbstract == true){
                    sumOfMethods += stoi(token);
                    allMethodsNums.push_back(stoi(token));
                }
            }

        }
        file.close();
        // Calculate the threshold
        float std = 0.0, threshold, avg = 0.0;
        int sumForStd = 0;
        if (numOfAbstracts > 0){
            avg = (static_cast< float >(sumOfMethods) / static_cast< float >(numOfAbstracts));
        }
        for (auto i = allMethodsNums.begin() ; i != allMethodsNums.end(); ++i){
            sumForStd += pow((*i-avg),2);
        }
        if (numOfAbstracts > 0){
            std = sqrt((static_cast< float >(sumForStd))/(static_cast< float >(numOfAbstracts)));
        }


        threshold = (avg + std) * 1.5;

        _threshold = RuleConfiguration::intForKey("SWISS_ARMY_KNIFE", threshold);


    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
            bool isClass = decl->isClass();
            bool hasDefinition = decl->hasDefinition();
            int methodCount = distance(decl->method_begin(), decl->method_end());
            bool isAbstract = false;
            if (isClass && hasDefinition){
                isAbstract = decl->isAbstract();
            }
            if (methodCount > this->_threshold && isAbstract)
            {
                string description = "C++ abstract class with " + toString<int>(methodCount) +
                                     " methods exceeds limit of " + toString<int>(_threshold);
                addViolation(decl, this, description);
            }
        return true;
    }
};

static RuleSet rules(new SwissArmyKnifeRule());

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

class RefusedBequestRule : public AbstractASTVisitorRule<RefusedBequestRule>
{
private:
    float _threshold;

public:
    virtual const string name() const override
    {
        return "refused bequest";
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
        thresholdMapping["REFUSED_BEQUEST"] =
            "The reporting threshold for too many methods, default value is 3.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("REFUSED_BEQUEST", REFUSED_BEQUEST_PERCENT);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        bool isClass = decl->isClass();
        bool hasDefinition = decl->hasDefinition();
        vector<string> classMethods;
        for (auto m = decl->method_begin() ; m != decl->method_end() ; m++ ) {
            string name = m->getNameAsString();
            classMethods.push_back(name);
        }
        int superClassMethods, numOfOverride = 0 , i;
        if (hasDefinition && isClass){
            for (auto b = decl->bases_begin() ; b != decl->bases_end() ; b++ ){
                superClassMethods = 0;
                std::ifstream file;
                file.open("/tmp/Data");
                string line;
                string delimiter = ";";
                string baseName = (b->getType()).getAsString();
                baseName.erase(baseName.begin(), baseName.begin()+6);
                size_t pos = 0;
                string token;
                int i =2;
                while (getline (file, line)) {
                    size_t pos = line.find(delimiter);
                    token = line.substr(0,pos);
                    if (token == baseName) {
                        for (auto j = classMethods.begin(); j != classMethods.end(); ++j) {
                            string methodName1 = " " + *j;
                            string methodName2 = ";" + *j;
                            size_t found1 = line.find(methodName1);
                            size_t found2 = line.find(methodName2);
                            if (found1 != string::npos || found2 != string::npos) {
                                numOfOverride++;
                            }
                        }

                        line.erase(0, pos + delimiter.length());
                        while ((pos = line.find(delimiter)) != string::npos) {
                            token = line.substr(0, pos);
                            if (i == 4) {
                                superClassMethods = stoi(token);
                                break;
                            }
                            line.erase(0, pos + delimiter.length());
                            i++;
                        }
                    }
                }
                if (superClassMethods != 0){
                    int ratio = (static_cast< float >(numOfOverride)/static_cast< float >(superClassMethods))*100;
                    if (ratio > _threshold){
                        string description = "C++  class with override more than half of it's super class";
                        addViolation(decl, this, description);
                    }
                }
                file.close();
            }
        }

        return true;
    }
};

static RuleSet rules(new RefusedBequestRule());

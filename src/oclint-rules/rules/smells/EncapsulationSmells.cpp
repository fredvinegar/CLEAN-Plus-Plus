#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <list>


using namespace std;
using namespace clang;
using namespace oclint;

class EncapsulationSmellsRule : public AbstractASTVisitorRule<EncapsulationSmellsRule>
{
private:
    int _threshold;


public:
    virtual const string name() const override
    {
        return "Encapsulation smells";
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
        _threshold = RuleConfiguration::intForKey("ENCAPSULATION_SMELLS", 1);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        if (hasDeficientEncapsulation(decl)){
            string description = "C++ class has Deficient Encapsulation.";
            addViolation(decl, this, description);
        }
        if (hasUnexploitedEncapsulation(decl)){
            string description = "C++ class has Unexploited Encapsulation.";
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

    bool hasUnexploitedEncapsulation(CXXRecordDecl *decl){
        list<string> classes = getClassesList();
        cout << "All classes are:" <<endl;
        for (auto c = classes.begin() ; c != classes.end() ; c++ ){
            cout << *c <<endl;
        }
        return false;
    }

    list<string> getClassesList(){
        list<string> classes;
        std::ifstream file;
        file.open("/robo/oclint-repo/oclint-scripts/Data");
        string line;
        string delimiter = ",";
        // Run over each line in Data
        while (getline(file, line)) {
            string token;
            size_t pos = line.find(delimiter)) != string::npos;
            token = line.substr(0, pos);
            classes.push_back(token);
            }
        return classes;
    }

    bool sameHierarchy(string met1, string met2){
        if (secIsAParentOfFirst(met1,met2) || secIsAParentOfFirst(met2,met1)){
            return true;
        }
        return false;
    }

    bool secIsAParentOfFirst(string met1, string met2) {
        // Is second is a parent of the first:

        queue<string> methodsToCheck;
        string delimiter = " ";
        methodsToCheck.push(met1);
        while (!methodsToCheck.empty()){
            string met = methodsToCheck.front();
            string parents = getParents(met);
            if ( parents.find(met2) != string::npos){
                return true;
            }else if (parents != ""){
                size_t pos = 0;
                string token;
                while ((pos = parents.find(delimiter)) != string::npos) {
                    token = parents.substr(0, pos);
                    methodsToCheck.push(token);
                    parents.erase(0, pos + delimiter.length());
                }
                methodsToCheck.push(parents);
            }
            methodsToCheck.pop();
        }
        return false;
    }

    string getParents(string child) {
        std::ifstream file;
        file.open("/robo/oclint-repo/oclint-scripts/Data");
        string line;
        string delimiter = ",";
        // Run over each line in Data
        while (getline(file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                if (i == 1 && token != child) {
                    break;
                }
                line.erase(0, pos + delimiter.length());
                if (i == 5) {
                    return token;
                }
                i++;
            }
        }
        return "";
    }

};

static RuleSet rules(new EncapsulationSmellsRule());

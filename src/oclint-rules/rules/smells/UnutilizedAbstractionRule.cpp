#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <regex>
#include <list>
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

class UnutilizedAbstractionRule : public AbstractASTVisitorRule<UnutilizedAbstractionRule>
{
private:
    int _threshold;
    Graph graph;
    list<string> classFields;
    list<string> classMethods;


public:
    virtual const string name() const override
    {
        return "unutilized abstraction";
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
        thresholdMapping["DESIGN_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("UNUTILIZED_ABSTRACTION", 1);

    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        this->classMethods = getMethodsList(decl);
        this->classFields = getFieldsList((decl));
        if (hasUnutilizedAbstraction(decl)){
            string description = "C++ class has Unutilized Abstraction.";
            addViolation(decl, this, description);
            return true;
        }
        return true;
    }


    bool hasUnutilizedAbstraction(CXXRecordDecl *decl){
        list<string> parentList = getParentsList(decl);
        string className = decl->getNameAsString();
        list<string> allClasses = getClassesList();
        int fanIn = getNumOfFanIn(className);
        if (parentList.size() == 0 ) {
            if (fanIn == 0) {
                return true;
            }
            return false;
        }else{
            for (auto parent = parentList.begin() ; parent != parentList.end() ; parent++){
                if (!isStringInList(*parent,allClasses)){
                    continue;
                }
                int fanInParent = getNumOfFanIn(*parent);
                if (fanInParent != 0 ){
                    return false;
                }
            }
        }
        return true;
    }

    list<string> getParentsList(CXXRecordDecl *decl) {
        list <string> parentsList;
        string className = decl->getNameAsString();
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        bool foundClass = false;
        string strOfParents;
        string delimiter = ";";
        // Run over each line in Data
        while (getline(file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                if (i == 1 && token != className) {
                    break;
                }

                line.erase(0, pos + delimiter.length());
                if (i == 5) {
                    strOfParents = token;
                    foundClass = true;
                    break;
                }
                i++;
            }

            if (foundClass) {
                break;
            }
        }
        if (strOfParents == ""){
            return parentsList;
        }
        string newDel = " ";
        size_t pos = 0;
        string token;
        while ((pos = strOfParents.find(newDel)) != string::npos) {
            token = strOfParents.substr(0, pos);
            parentsList.push_back(token);
            strOfParents.erase(0, pos + newDel.length());
        }parentsList.push_back(strOfParents);
        return parentsList;
    }

    int getNumOfFanIn(string className) {
        string theRegexMethod = "^" + className + ":";
        string tempNum;
        int sum = 0;
        std::ifstream file;
        file.open("/tmp/NumOfFanIn");
        string line;
        int sumOfOuts = 0;
        string delimiter = ",";
        // Run over each line in Data
        while (getline(file, line)) {
            size_t pos = 0, pos1 = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                if (regex_search(token , regex(theRegexMethod))){
                    pos1 = token.find(":");
                    token.erase(0, pos1+1);
                    sum += stoi(token);
                }

            }
        }
        file.close();
        return sum;
    }
    list<string> getMethodsList(CXXRecordDecl *decl){
        list<string> methodsList;
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ) {
            methodsList.push_back((*method)->getNameAsString());
        }
        return methodsList;
    }

    list<string> getFieldsList(CXXRecordDecl *decl){
        list<string> fieldsList;
        for (auto field = decl->field_begin() ; field != decl->field_end() ; field++ ){
            fieldsList.push_back((*field)->getNameAsString());
        }
        return fieldsList;
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

    bool isStringInList(string str, list<string> listStrs){
        for (auto s = listStrs.begin() ; s != listStrs.end() ; s++ ){
            if ((*s) == str){
                return true;
            }
        }
        return false;
    }


};

static RuleSet rules(new UnutilizedAbstractionRule());

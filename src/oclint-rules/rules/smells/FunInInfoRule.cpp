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

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class FunInInfoRule : public AbstractASTVisitorRule<FunInInfoRule>
{
private:
    int _threshold;
    list<string> _allClasses;


public:
    virtual const string name() const override
    {
        return "fun in info";
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
        thresholdMapping["MODULARIZATION_SMELLS"] =
            "explanation...";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("MODULARIZATION_SMELLS", 1);
        _allClasses = getClassesList();
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        if (hasBrokenModularization(decl)){
            string description = "C++ class has Broken Modularization.";
            addViolation(decl, this, description);
        }
        if (hasCyclicDependentModularization(decl)){
            string description = "C++ class has CyclicDependent Modularization.";
            addViolation(decl, this, description);
        }
        if (hasInsufficientModularization(decl)){
            string description = "C++ class has Insufficient Modularization.";
            addViolation(decl, this, description);
        }
        if (hasHubLikeModularization(decl)){
            string description = "C++ class has Hub Like Modularization.";
            addViolation(decl, this, description);
        }

        return true;
    }

    bool hasBrokenModularization(CXXRecordDecl *decl){
        cout << "WOrkWorkWork" <<endl;
        int numOfMethods = 0;
        int numOfFields = 0;
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            numOfMethods++;
        }
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            numOfFields++;
        }
        if (numOfMethods==0 && numOfFields>5){
            return true;
        }
        return false;
    }

    bool hasCyclicDependentModularization(CXXRecordDecl *decl){
        return false;
    }

    bool hasInsufficientModularization(CXXRecordDecl *decl){
        int sumComplexity = 0;
        int numOfPublicMethods = 0;
        int numOfMethods = 0;
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            numOfMethods++;
            if ((*f)->getAccess() == clang::AS_public){
                numOfPublicMethods++;
            }
            sumComplexity += calculateCyclomaticComplexity(*f);
        }
        if (numOfMethods >= 30 || numOfPublicMethods >=20 || sumComplexity >=100){
            return true;
        }
        return false;
    }

    bool hasHubLikeModularization(CXXRecordDecl *decl){
        int numOfClassFields = 0;
        int allClassesInMethod = 0;
        string temp;
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            temp = ((*f)->getParent())->getNameAsString();
            if (isInClassList(temp)){
                numOfClassFields++;
            }
        }
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            for (auto c = _allClasses.begin() ; c != _allClasses.end() ; c++){
                allClassesInMethod += countStringInMethod(*f,*c);
            }
        }
        int numOfFunOut = allClassesInMethod + numOfClassFields;

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
            size_t pos = line.find(delimiter);
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

    int countStringInMethod (FunctionDecl *decl, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        Stmt *funcBody = decl->getBody();
        SourceRange range = funcBody->getSourceRange();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string text = get_source_text_raw(printable_range, *TheSourceMgr);
        string theRegex = regex_begin + str + regex_begin;
        if (regex_search(text , regex(theRegex))){
            regex re(theRegex);
            auto words_begin = std::sregex_iterator(text.begin(), text.end(), re);
            auto words_end = std::sregex_iterator();
            return distance(words_begin, words_end);
        } else return 0;

    }
    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}

    int calculateCyclomaticComplexity(FunctionDecl *decl){
        int sum = 1;
        list<string> stmtList ({"if","switch","for","while","for_each"});
        for (auto stm = stmtList.begin() ; stm != stmtList.end() ; stm++){
            sum += countStringInMethod(decl,*stm);
        }
        return sum;
    }

    bool isInClassList(string str){
        for (auto stm = _allClasses.begin() ; stm != _allClasses.end() ; stm++){
            if (*stm == str){
                return true;
            }
        }
        return false;
    }
    //// non relevance, going to be in another file!
//    int getNumOfFuncIn(CXXRecordDecl *decl) {
//        std::ifstream file;
//        file.open("/robo/oclint-repo/oclint-scripts/Data");
//        string line;
//        float sumOfTCC = 0;
//        int numOfClasses = 0;
//        string delimiter = ",";
//        vector<int> allMethodsNums;
//        // Run over each line in Data
//        while (getline(file, line)) {
//            int i = 1;
//            size_t pos = 0;
//            string token;
//            // For each line take the relevance tokens
//            while ((pos = line.find(delimiter)) != string::npos) {
//                token = line.substr(0, pos);
//                line.erase(0, pos + delimiter.length());
//                if (i == 1) {
//                    if (token != decl->getNameAsString()) {
//                        break;
//                    } else if (i == 8) {
//                        cout << token;
//                        break;
//                    }
//                    i++;
//                }
//            }
//            file.close();
//        }
//    }


};

static RuleSet rules(new FunInInfoRule());

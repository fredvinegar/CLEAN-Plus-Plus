#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <regex>
#include <list>
#include <map>


using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class SpaghettiCodeRule : public AbstractASTVisitorRule<SpaghettiCodeRule>
{
private:

    int _threshold;

public:
    virtual const string name() const override
    {
        return "spaghetti code";
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
        thresholdMapping["SPAGHETTI_CODE"] =
            "One or more public fields.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        _threshold = RuleConfiguration::intForKey("SPAGHETTI_CODE", 1);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        float avgLength = getMLOCThreshold();



        list<FunctionDecl*> longMethods;
        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ){
            Stmt *stmt = f->getBody();
            if (stmt == 0){
                continue;
            }
            int length = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            if (length > avgLength){
                longMethods.push_back(*f);
            }
        }

        for (auto listfi = longMethods.begin() ; listfi != longMethods.end() ; listfi++){
            string methodName = (*listfi)->getNameAsString();
            for (auto listfj = longMethods.begin() ; listfj != longMethods.end() ; listfj++){
                if (methodName == (*listfj)->getNameAsString()){
                    continue;
                } else{
                    if (hasStringInMethod((*listfj),methodName)){
                        string description = "C++ class with at least two long methods interacting between them through method calls or shared fields.";
                        addViolation(decl, this, description);
                        return true;
                    }
                }
            }
        }

        list<string> fields;
        map<string,list<string>> methodsFieldsMap;
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        string regex_begin = "[^a-zA-Z0-9]";
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            fields.push_back((*f)->getNameAsString());
        }

        for (auto f = longMethods.begin() ; f != longMethods.end() ; f++ ){
            list<string> fieldsInMethods;
            string methodName = (*f)->getNameAsString();

            for (auto field = fields.begin() ; field != fields.end() ; field++ ){
                if (hasStringInMethod(*f,*field)){
                    fieldsInMethods.push_back(*field);
                }
            }
            methodsFieldsMap.insert({methodName , fieldsInMethods});
        }

        map<string,list<string>>::iterator m;
        map<string,list<string>>::iterator n;

        for (m = methodsFieldsMap.begin() ; m != methodsFieldsMap.end() ; m++ ){
            for (n = m ; n != methodsFieldsMap.end() ; n++){
                if (n == m){
                    continue;
                }
                if (hasCommon(m->second , n->second)){
                    string description = "C++ class with at least two long methods interacting between them through method calls or shared fields.";
                    addViolation(decl, this, description);
                    return true;
                }
            }
        }


        return true;
    }

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}

    bool hasCommon (list<string> l1 , list <string> l2){
        for (auto i = l1.begin() ; i != l1.end() ; i++){
            for (auto j = l2.begin() ; j != l2.end() ; j++){
                if ((*i) == (*j)){
                    return true;
                }
            }
        }
        return false;
    }

    float getMLOCThreshold(){
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        int sumOfMLOC = 0;
        int numOfMethods = 0;
        string delimiter = ";";
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==2) {
                    sumOfMLOC += stoi(token);
                    numOfMethods += 1;
                    break;
                }
                i ++;
                line.erase(0, pos+delimiter.length());
            }
        }
        file.close();
        // Calculate the threshold
        float  avg = 0.0;
        if (numOfMethods > 0){
            avg = (static_cast< float >(sumOfMLOC) / static_cast< float >(numOfMethods));
        }

        return avg;
    }

    string cleanCommentsFromCodeText(string origin){
        string delimiter1 = "//";
        string delimiter2 = "\n";
        string delimiter3 = "/*";
        string delimiter4 = "*/";
        size_t pos1 = 0;
        size_t pos2 = 0;
        size_t pos3 = 0;
        size_t pos4 = 0;
        while ((pos1 = origin.find(delimiter1)) != string::npos){
            pos2 = origin.find(delimiter2,pos1);
            origin.erase(pos1,pos2-pos1);
        }
        while ((pos3 = origin.find(delimiter3)) != string::npos){
            pos4 = origin.find(delimiter4,pos3);
            origin.erase(pos3,pos4-pos3);
        }
        return origin;
    }


    bool hasStringInMethod (FunctionDecl *decl, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        Stmt *funcBody = decl->getBody();
        if (funcBody == 0){
            return false;
        }
        SourceRange range = funcBody->getSourceRange();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string text_origin = get_source_text_raw(printable_range, *TheSourceMgr);
        string text = cleanCommentsFromCodeText(text_origin);
        string theRegex = regex_begin + str + regex_begin;
            if (regex_search(text , regex(theRegex))){
                return true;
            } else return false;

    }

};

static RuleSet rules(new SpaghettiCodeRule());


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
#include "oclint/util/Thresholds.h"



using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class GodClassRule : public AbstractASTVisitorRule<GodClassRule>
{
private:

    int _threshold;

public:
    virtual const string name() const override
    {
        return "god class";
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
        thresholdMapping["GOD_CLASS"] =
            "One or more public fields.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        float sumOfTCC = 0;
        int numOfClasses = 0;
        string delimiter = ";";
        vector<int> allMethodsNums;
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                line.erase(0, pos+delimiter.length());
                if (i == 6 ){
                    sumOfTCC += stof(line);
                    numOfClasses ++;
                }
                i++;

            }
        }
        file.close();
        // Calculate the threshold
        float avg = 0.0;
        int threshold;
        avg = (static_cast< float >(sumOfTCC) / static_cast< float >(numOfClasses));

        threshold = avg * 100;
        _threshold = RuleConfiguration::intForKey("GOD_CLASS", threshold);
    }


    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {

        list<string> fields;
        map<string,list<string>> methodsFieldsMap;
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        string regex_begin = "[^a-zA-Z0-9]";
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            fields.push_back((*f)->getNameAsString());
        }
        int numOfMethods =0;



        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ){
            numOfMethods ++ ;
            string methodName = f->getNameAsString();
            list<string> fieldsInMethods;
            Stmt *funcBody = (*f)->getBody();
            if (funcBody == 0){
                return false;
            }
            SourceRange range = funcBody->getSourceRange();
            auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
            auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
            auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
            auto printable_range = clang::SourceRange{start_loc, end_loc};
            string text = get_source_text_raw(printable_range, *TheSourceMgr);
            for (auto field = fields.begin() ; field != fields.end() ; field++ ){
                string theRegex = regex_begin + *field + regex_begin;
                if (regex_search(text , regex(theRegex))){
                    fieldsInMethods.push_back(*field);
                }
            }
            methodsFieldsMap.insert({methodName , fieldsInMethods});
        }

        int connected = 0 ;

        map<string,list<string>>::iterator m;
        map<string,list<string>>::iterator n;


        for (m = methodsFieldsMap.begin() ; m != methodsFieldsMap.end() ; m++ ){
            for (n = m ; n != methodsFieldsMap.end() ; n++){
                if (n == m){
                    continue;
                }
                if (hasCommon(m->second , n->second)){
                    connected ++;
                }
            }
        }

        float np = static_cast< float >(numOfMethods*(numOfMethods-1)/2);
        float TCC = static_cast< float >(connected)/np;

        int length = getNumLineOfClass(decl);

        float decThreshold = static_cast< float >(_threshold)/100.;

        if (TCC < decThreshold && length > GOD_CLASS_LOC)
        {
            string description = "C++ class with " + toString<int>(length) + " lines and "+ toString<float>(TCC) +
                                 " TCC exceeds limit of " + toString<float>(decThreshold);
            addViolation(decl, this, description);
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

    int getNumLineOfClass(CXXRecordDecl *decl)
    {
        int numLine = 2;
        numLine += distance(decl->field_begin(), decl->field_end());
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            Stmt *stmt = method->getBody();
            if  (stmt == 0 ) {
                continue;
            }
            const int lineCount = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            numLine += lineCount;
        }
        return numLine;
    }

};

static RuleSet rules(new GodClassRule());
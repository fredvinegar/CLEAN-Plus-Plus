#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include "oclint/util/ASTUtil.h"
#include <regex>
#include <list>
#include <map>
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"


using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;


class NumOfFunInRule : public AbstractASTVisitorRule<NumOfFunInRule>
{
private:
    std::fstream file;

public:
    virtual const string name() const override
    {
        return "num of fun in";
    }

    virtual int priority() const override
    {
        return 1;
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

//    virtual const std::map<std::string, std::string> thresholds() const override
//    {
//        std::map<std::string, std::string> thresholdMapping;
//        thresholdMapping["AGGREGATE_INFO_RULE"] =
//            "agg.";
//        return thresholdMapping;
//    }
#endif

    virtual void setUp() override
    {
    }



    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        file.open ("/robo/oclint-repo/oclint-scripts/NumOfFunIn",std::ios::app);

        if ( !file.is_open() ){
            cout << "no file" << endl;
        }

        string className = decl->getNameAsString();
        list<string> allClasses = getClassesList();
        for(auto c = allClasses.begin() ; c != allClasses.end() ; c++){
            cout << "class is " <<*c <<endl;
            if (*c == decl->getNameAsString()){
                file << *c << ":" << 0 << ",";
            }else{
                int numOfOut = getNumOfClassOut(*c,decl);
                file << *c << ":" << numOfOut << ",";
            }
        }
        file << "\n";
        file.close();

        return true;
    }

    int getNumOfClassOut(string classToCheck, CXXRecordDecl *decl){
        cout << "class to check is " <<classToCheck <<endl;
        int numOfFunOut = 0;

        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ) {
            numOfFunOut += countStringInMethod(*f,classToCheck);
        }
        cout << numOfFunOut <<endl;
        return numOfFunOut;
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
};

static RuleSet rules(new NumOfFunInRule());

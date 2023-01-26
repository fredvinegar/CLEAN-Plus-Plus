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


class MethodsInfoRule : public AbstractASTVisitorRule<MethodsInfoRule>
{
private:
    std::fstream file;
    list<string> allClasses;


public:
    virtual const string name() const override
    {
        return "methods info";
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
//        cout << decl->getNameAsString() << endl;
        string className = decl->getNameAsString();
        if (std::find((this->allClasses).begin(), (this->allClasses).end(), className) != (this->allClasses).end()){
            return true;
        }

        (this->allClasses).push_back(className);
        file.open ("/tmp/Methods",std::ios::app);
        if ( !file.is_open() ){
            cout << "no file" << endl;
        }
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
//            cout << method->getNameAsString() << endl;
            Stmt *stmt = method->getBody();
            if (stmt == 0){
                continue;
            }
//            cout << 1 << endl;
            int length = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
//            cout << 2 << endl;
            int params_num = method-> getNumParams();
//            cout << 3 << endl;
            int CC = calculateCyclomaticComplexityOfMethod(*method);
            bool isVirtual = method->isVirtual();
            file << className << "." << method->getNameAsString() << ";" << length << ";" << params_num << ";" << CC << ";" << isVirtual << "\n";


        }


        file.close();

        return false;
    }



    int calculateCyclomaticComplexityOfMethod(FunctionDecl *decl){
        Stmt *theStmt = decl->getBody();
        if (theStmt == 0 ){
            return 0;
        }
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        SourceRange range = theStmt->getSourceRange();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string method_text = get_source_text_raw(printable_range, *TheSourceMgr);
        method_text = cleanCommentsFromCodeText(method_text);

        return 1 + countStringInMethod(method_text, "if") + countStringInMethod(method_text, "while") + countStringInMethod(method_text, "for") + countStringInMethod(method_text, "case");
    }

    int countStringInMethod (string method_text, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        string theRegex = regex_begin + str + regex_begin;
        if (regex_search(method_text , regex(theRegex))){
            regex re(theRegex);
            auto words_begin = std::sregex_iterator(method_text.begin(), method_text.end(), re);
            auto words_end = std::sregex_iterator();
            return distance(words_begin, words_end);
        } else return 0;

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

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}
};

static RuleSet rules(new MethodsInfoRule());

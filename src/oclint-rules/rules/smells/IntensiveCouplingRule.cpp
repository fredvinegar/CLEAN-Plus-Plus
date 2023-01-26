#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "oclint/util/Thresholds.h"
#include "oclint/RuleConfiguration.h"
#include <cmath>
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <list>
#include <map>
#include "oclint/metric/MethodMaxNestingMetric.h"


using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class IntensiveCouplingRule : public AbstractASTVisitorRule<IntensiveCouplingRule>
{

public:
    virtual const string name() const override
    {
        return "intensive coupling";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Organic Method Smell";
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


    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        list<string> methods_list = getMethodsList();
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            const int maxNesting = (MethodMaxNestingMetric{}).calculateCXX(*method);
            const int cint = couplingIntensityCalc(*method,methods_list);
            const float cdisp = couplingDispersionCalc(*method, methods_list);
            bool callsManyDispersedInFew = cint > INTENSIVE_COUPLING_CINT && cdisp < DISPERSED_COUPLING_CDISP;
            bool callsMoreThanFewInVeryFewClasses = cint > INTENSIVE_COUPLING_CINT/2 && cdisp < INTENSIVE_COUPLING_CDISP;
            if ((callsManyDispersedInFew || callsMoreThanFewInVeryFewClasses) && maxNesting > INTENSIVE_COUPLING_MAXNESTING)
            {
                string description = "C++ class has intensive coupling.";
                addViolation(decl, this, description);
            }
        }

        return true;
    }
    list<string> getMethodsList(){
        list<string> Methods;
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        string delimiter = ";";
        string delimiter1 = ".";
        // Run over each line in Data
        while (getline(file, line)) {
            string token;
            size_t pos = line.find(delimiter);
            size_t pos1 = line.find(delimiter1);
            token = line.substr(0, pos);
            Methods.push_back(token);
        }
        return Methods;
    }

//    list<string> getMethodsList(CXXRecordDecl *decl){
//        list<string> methodList;
//        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
//            methodList.push_back(method->getNameAsString());
//        }
//        return methodList;
//    }

    int couplingIntensityCalc(CXXMethodDecl *decl, list<string> methods_list)
    {
        int count = 0;
        for (auto method = methods_list.begin(); method != methods_list.end(); method++){
            string m = *method;
            string method_name = m.substr(m.find('.')+1);
            count = count + countStringInMethod(decl, method_name);
        }
        return count;
    }

    bool hasStringInMethod(FunctionDecl *decl, string str)
    {
        string regex_begin = "[^a-zA-Z0-9]";
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        Stmt *funcBody = decl->getBody();
        if (funcBody==0){
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


    float couplingDispersionCalc(CXXMethodDecl *decl, list<string> methods_list)
    {
        int CINT = couplingIntensityCalc(decl, methods_list);
        int count = 0;
        for (auto method = methods_list.begin(); method != methods_list.end(); method++){
            string m = *method;
            string method_name2 = m.substr(0,m.find('.'));
            string method_name1 = m.substr(m.find('.')+1);
            if (method_name2 != decl->getParent()->getNameAsString()) {
                count = count + countStringInMethod(decl, method_name1);
            }

        }
        if (CINT == 0){
            return 0;
        }
        float ans = (float)count/(float)CINT;
        return ans;
    }

    int countStringInMethod (FunctionDecl *decl, string str){
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
            regex re(theRegex);
            auto words_begin = std::sregex_iterator(text.begin(), text.end(), re);
            auto words_end = std::sregex_iterator();
            return distance(words_begin, words_end);
        } else return 0;

    }


};

static RuleSet rules(new IntensiveCouplingRule());

#include "oclint/metric/StringInMethodMetric.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <regex>
#include <list>
#include "clang/Lex/Lexer.h"
#include "oclint/metric/StringInMethodMetric.h"


using namespace std;
using namespace oclint;
clang::LangOptions lo;

bool StringInMethodMetric::hasStringInMethod(FunctionDecl *decl, string str)
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

    string text = get_source_text_raw(printable_range, *TheSourceMgr);
    string theRegex = regex_begin + str + regex_begin;
    if (regex_search(text , regex(theRegex))){
        return true;
    } else return false;
}

int StringInMethodMetric::countStringInMethod (FunctionDecl *decl, string str){
    cout << "inside stringIn" <<endl;
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
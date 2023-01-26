#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include "oclint/util/ASTUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>
#include <list>
#include "oclint/util/Thresholds.h"
#include "clang/Lex/Lexer.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"


using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class ComplexMethodRule : public AbstractASTVisitorRule<ComplexMethodRule>
{
//    list<Stmt*> stmtList;

public:
    virtual const string name() const override
    {
        return "complex method";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Implementation Smell";
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


    bool VisitCXXRecordDecl  (CXXRecordDecl   *decl)
    {
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            const int cc = calculateCyclomaticComplexityOfMethod(*method);
            if (cc >= CC_COMPLEX_METHOD )
            {
                string description = "C++ class has complex method.";
                addViolation(decl, this, description);
            }

        }

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

        return 1 + countStringInMethod(method_text, "if") + countStringInMethod(method_text, "while") + countStringInMethod(method_text, "for") + countStringInMethod(method_text, "case") ;
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

//    int calculateCyclomaticComplexityOfMethod(FunctionDecl *decl){
//        cout << "______________" << decl->getNameAsString() << "___________" << endl;
//        int cc = 0;
//        Stmt *theStmt = decl->getBody();
////        vector<Stmt*>* stmtList;
////        stmtList->push_back(theStmt);
//        getAllStmtList(theStmt, cc);
////        cout << "the list size is " <<stmtList->size() <<endl;
////        for (auto s = stmtList->begin() ; s != stmtList->end() ; s++ ){
////                clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
////                SourceRange range = (*s)->getSourceRange();
////                SourceLocation b = range.getBegin();
////                SourceLocation e = range.getEnd();
////                FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);
////
////                auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
////                auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
////                auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
////                auto printable_range = clang::SourceRange{start_loc, end_loc};
////
////                string text = get_source_text_raw(printable_range, *TheSourceMgr);
////                cout << text << "\n\n"<<endl;
////        }
////        if (theStmt != 0) {
////            for (auto child = theStmt->child_begin(); child != theStmt->child_end(); child++) {
//
////                clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
////                SourceRange range = child->getSourceRange();
////                SourceLocation b = range.getBegin();
////                SourceLocation e = range.getEnd();
////                FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);
////
////                auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
////                auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
////                auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
////                auto printable_range = clang::SourceRange{start_loc, end_loc};
////
////                string text = get_source_text_raw(printable_range, *TheSourceMgr);
////                cout << text << endl;
////                cout << "_______________________________________" << endl;
////
////            }
////        }
//
//        return cc;
//    }
//
//    void getAllStmtList (Stmt *theStmt, int &cc) {
//        if (theStmt != 0) {
//            int methodCount = distance(theStmt->child_begin(), theStmt->child_end());
//            cout << "distance " <<methodCount << endl;
//            if (distance(theStmt->child_begin(), theStmt->child_end()) > 0){
//                for (auto child = theStmt->child_begin(); child != theStmt->child_end(); child++) {
//                    clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
//                    SourceRange range = child->getSourceRange();
//                    SourceLocation b = range.getBegin();
//                    SourceLocation e = range.getEnd();
//                    FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);
//
//                    auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
//                    auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
//                    auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
//                    auto printable_range = clang::SourceRange{start_loc, end_loc};
//
//                    string text = get_source_text_raw(printable_range, *TheSourceMgr);
//                    cout << text << "\n"<<endl;
//
//                    if (isACCType(*child)){
//                        cout << "here" <<endl;
//                        cout << "here1" <<endl;
//
////                    cc++;
//                    }
//
//                    cout << "here2" <<endl;
//                    getAllStmtList(*child, cc);
//
//
//                }
//            }else{
//                cout << "here3" << endl;
//            }
//
//        }
//    }
//
//    bool isACCType(Stmt * theStmt){
//        if (isa<CXXCatchStmt>(*theStmt)) {
//            cout << "im CXXCatchStmt" << endl;
//            return true;
//        }
//        if (isa<CXXTryStmt>(*theStmt)) {
//            cout << "im CXXTryStmt" << endl;
//            return true;
//        }
//        if (isa<ObjCAtCatchStmt>(*theStmt)) {
//            cout << "im ObjCAtCatchStmt" << endl;
//            return true;
//        }
//        if (isa<ObjCAtTryStmt>(*theStmt)) {
//            cout << "im ObjCAtTryStmt" << endl;
//            return true;
//        }
//        if (isa<BinaryOperator>(*theStmt)) {
//            cout << "im BinaryOperator" << endl;
//            return true;
//        }
//        if (isa<ConditionalOperator>(*theStmt)) {
//            cout << "im ConditionalOperator" << endl;
//            return true;
//        }
//        if (isa<CaseStmt>(*theStmt)) {
//            cout << "im CaseStmt" << endl;
//            return true;
//        }
//        if (isa<SwitchCase>(*theStmt)) {
//            cout << "im SwitchCase" << endl;
//            return true;
//        }
//        if (isa<SwitchStmt>(*theStmt)) {
//            cout << "im SwitchStmt" << endl;
//            return true;
//        }
//        if (isa<WhileStmt>(*theStmt)) {
//            cout << "im WhileStmt" << endl;
//            return true;
//        }
//        if (isa<DoStmt>(*theStmt)) {
//            cout << "im DoStmt" << endl;
//            return true;
//        }
//        if (isa<ObjCForCollectionStmt>(*theStmt)) {
//            cout << "im ObjCForCollectionStmt" << endl;
//            return true;
//        }
//        if (isa<ForStmt>(*theStmt)) {
//            cout << "im ForStmt" << endl;
//            return true;
//        }
//        if (isa<IfStmt>(*theStmt)) {
//            cout << "im IfStmt" << endl;
//            return true;
//        }
//        return false;
//
//    }

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}



};

static RuleSet rules(new ComplexMethodRule());

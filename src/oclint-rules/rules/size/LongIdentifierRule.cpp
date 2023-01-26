#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "oclint/util/Thresholds.h"
#include <cmath>
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <list>
#include <map>
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class LongIdentifierRule : public AbstractASTVisitorRule<LongIdentifierRule>
{

public:
    virtual const string name() const override
    {
        return "long identifier";
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


    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        bool hasLongIdentifier = false; //if there is one identifier that is long it will change it to true.
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ) {
            // Find long local variable
            Stmt *theStmt = method->getBody();
            if (theStmt != 0) {
                for (auto child = theStmt->child_begin() ; child != theStmt->child_end() ; child++ ){

                    if (isa<clang::DeclStmt>(*child)){
                        SourceRange range = child -> getSourceRange ();
                        string text = getAsText(range);
                        size_t pos = 0, equalPos = 0;
                        pos = text.find(" ");
                        text.erase(0, pos+1);
                        text.erase(std::remove_if(text.begin(), text.end(), ::isspace),text.end());
                        string token, localVar;
                        string delimiter = ",";
                        while ((pos = text.find(delimiter)) != string::npos){
                            token = text.substr(0,pos);
                            equalPos = token.find("=");
                            if (equalPos != string::npos) {
                                token.erase(equalPos, token.length()-1);
                            }
                            if (token.length() >= LONG_IDENTIFIER){
//                                cout << method->getNameAsString() << " long variable" << endl;
                                hasLongIdentifier = true;
                            }
                            text.erase(0, pos+delimiter.length());
                        }
                        equalPos = text.find("=");
                        if (equalPos != string::npos){
                            text.erase(equalPos, text.length()-1);
                            if(text.length() >= LONG_IDENTIFIER){
//                                cout << method->getNameAsString() << " long variable" << endl;
                                hasLongIdentifier = true;
                            }
                        }
                        else{
                            if((text.length()-1) >= LONG_IDENTIFIER){
//                                cout << method->getNameAsString() << " long variable" << endl;
                                hasLongIdentifier = true;
                            }
                        }
                    }
                }
            }

            // Find long parameters
            for (auto param = method->param_begin() ; param != method->param_end() ; param++ ){
                string paramName = (*param)->getNameAsString();
                if (paramName.length() >= LONG_IDENTIFIER){
//                    cout << method->getNameAsString() << " long param" << endl;
                    hasLongIdentifier = true;
                }
            }
            // Find long fields
            list <string> longFieldsList = getLongFieldsList(decl);
            if (!longFieldsList.empty()){
                for (auto field = longFieldsList.begin() ; field != longFieldsList.end() ; field++ ){
                    if (hasStringInMethod(*method,*field)){
//                        cout << method->getNameAsString() << " long field" << endl;
                        hasLongIdentifier = true;
                    }
                }
            }
        }
        if (hasLongIdentifier){
            string description = "C++ method has long identifier.";
            addViolation(decl, this, description);
        }
        return true;
    }

    list <string> getLongFieldsList(CXXRecordDecl *decl){
        list <string> longFieldsList;
        string fieldName;
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            fieldName = (*f)->getNameAsString();
            if (fieldName.length() >= LONG_IDENTIFIER){
                longFieldsList.push_back(fieldName);
            }
        }
        return longFieldsList;
    }

    string getAsText(SourceRange range){
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string str = get_source_text_raw(printable_range, *TheSourceMgr);

        return str;
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

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}
};

static RuleSet rules(new LongIdentifierRule());

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
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <list>
#include <map>

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class MagicNumberRule : public AbstractASTVisitorRule<MagicNumberRule>
{
private:
    bool hasLiteral;
    string arrayStmt;

public:
    virtual const string name() const override
    {
        return "magic number";
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
    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        hasLiteral = false;
        return true;
    }

    bool VisitDeclStmt(clang::DeclStmt *decl){
        SourceRange range = decl -> getSourceRange ();
        string text = getAsText(range);
        size_t pos1 = text.find("[");
        size_t pos2 = text.find("]");
        if (pos1 != string::npos && pos2 != string::npos){
            arrayStmt = text;
        }
        return true;
    }

    bool VisitIntegerLiteral(clang::IntegerLiteral *literal) {
        SourceRange range = literal -> getSourceRange ();
        string liText = getAsText(range);
        size_t pos = arrayStmt.find(liText);
        if (pos != string::npos){
            arrayStmt.erase(0, pos + liText.length());
        } else{

            if (literal->getValue() != 0 && literal->getValue() != 1 && !hasLiteral){
                string description = "C++ method has magic number.";
                addViolation(literal, this, description);
                hasLiteral = true;
                return false;
            }
        }
        return true;
    }
    bool VisitFloatingLiteral(clang::FloatingLiteral *literal) {
        llvm::APFloat val = literal->getValue();
        if (!val.isZero()  && !val.isExactlyValue(1.0) && !hasLiteral){
            string description = "C++ method has magic number.";
            addViolation(literal, this, description);
            hasLiteral = true;
            return false;
        }

        return true;
    }

    bool VisitFixedPointLiteral(clang::FixedPointLiteral *literal) {
        if (literal->getValue() != 0 && literal->getValue() != 1 && !hasLiteral){
            string description = "C++ method has magic number.";
            addViolation(literal, this, description);
            hasLiteral = true;
            return false;
        }

        return true;
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

        return cleanCommentsFromCodeText(str);
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

static RuleSet rules(new MagicNumberRule());

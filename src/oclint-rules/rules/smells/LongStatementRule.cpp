#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "oclint/metric/MethodCouplingDispersionMetric.h"
#include "oclint/metric/MethodMaxNestingMetric.h"
#include "oclint/metric/MethodCouplingIntensityMetric.h"
#include "oclint/util/Thresholds.h"
#include "oclint/metric/MethodNOAVMetric.h"
#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include <vector>
#include <cmath>
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "oclint/metric/MethodMaxNestingMetric.h"
#include "oclint/metric/MethodNumOfLocalVarsMetric.h"
#include "oclint/metric/MethodNOAVMetric.h"
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
#include "clang/Lex/Lexer.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "oclint/metric/StringInMethodMetric.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class LongStatementRule : public AbstractASTVisitorRule<LongStatementRule>
{

public:
    virtual const string name() const override
    {
        return "long statement";
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
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ) {
            Stmt *theStmt = method->getBody();
            if (theStmt != 0) {
                for (auto child = theStmt->child_begin() ; child != theStmt->child_end() ; child++ ){
                        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
                        SourceRange range = child -> getSourceRange ();
                        SourceLocation b = range.getBegin();
                        SourceLocation e = range.getEnd();
                        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

                        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
                        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
                        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
                        auto printable_range = clang::SourceRange{start_loc, end_loc};

                        string statement = get_source_text_raw(printable_range, *TheSourceMgr);

                        if (statement.length() > LONG_STATEMENT) {
                            string description = "C++ class has long statement.";
                            addViolation(decl, this, description);
                        }

                }
            }
        }return true;
    }


    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}
};

static RuleSet rules(new LongStatementRule());

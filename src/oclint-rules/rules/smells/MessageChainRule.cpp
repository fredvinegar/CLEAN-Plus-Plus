#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "oclint/util/Thresholds.h"
#include <vector>
#include <cmath>
#include "oclint/util/ASTUtil.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <list>
#include <map>
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class MessageChainRule : public AbstractASTVisitorRule<MessageChainRule>
{

public:
    virtual const string name() const override
    {
        return "message chain";
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
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            const int maxCallChain = maxCallChainCalc(*method);
            if (maxCallChain > MAX_CALL_CHAIN_THRESHOLD)
            {
                string description = "C++ class has message chain.";
                addViolation(decl, this, description);
            }
        }

        return true;
    }

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}


    int maxCallChainCalc (FunctionDecl *decl){
        string regex_begin = "[a-zA-Z\\_\\d]+\\.[a-zA-Z\\_\\d]+\\([a-zA-Z0-9\\_]*\\)";
        string regex_continue = "(\\.[a-zA-Z\\_\\d]+\\([a-zA-Z0-9\\_]*\\))+";
        regex re(regex_continue);
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

        string originText = get_source_text_raw(printable_range, *TheSourceMgr);
        string text = cleanCommentsFromCodeText(originText);
        size_t pos = 0;
        string line;
        string delimiter = "\n";
        int maxChain = 0;
        while ((pos = text.find(delimiter)) != string::npos){
            line = text.substr(0,pos);
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            int count_chain = 0;
            std::string temp;
            for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), re);i != std::sregex_iterator();++i) {
                std::smatch match = *i;
                temp = match.str();
                count_chain = std::count(temp.begin(), temp.end(), '.');
                if (count_chain > maxChain) {
                    maxChain = count_chain;
//                    cout << line << endl;
//                    cout << maxChain << endl;
                }
            }


//            if (regex_search(line , regex(regex_begin))){
//                auto words_begin = std::sregex_iterator(line.begin(), line.end(), re);
//                auto words_end = std::sregex_iterator();
//                count_chain += distance(words_begin, words_end);
//            }
//            if (count_chain > maxChain){
//                maxChain = count_chain;
//                cout << line << endl;
//                cout << maxChain << endl;
//            }
            text.erase(0, pos+delimiter.length());
        }

        return maxChain;

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

};

static RuleSet rules(new MessageChainRule());

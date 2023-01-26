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

class AbstractFunctionCallFromConstructorRule : public AbstractASTVisitorRule<AbstractFunctionCallFromConstructorRule>
{

public:
    virtual const string name() const override
    {
        return "abstract function call from constructor";
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
        list<string> virtualMethods = getVirtualMethodsList();
        string className = decl->getNameAsString();
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            string methodName = method->getNameAsString();
            if (methodName == className){
                for (auto virt = virtualMethods.begin(); virt != virtualMethods.end(); virt++){
                    if (hasStringInMethod(*method, *virt) == true){
                        string description = "C++ class has constructor calls to abstract function.";
                        addViolation(decl, this, description);
                    }
                }
            }
        }

        return true;
    }

    list<string> getVirtualMethodsList(){
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        list <string> virtualMethods;
        string delimiter = ";";
        string name;
        bool isVirtual;
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==1) {
                    string delimiter1 = ".";
                    size_t pos1 = token.find(delimiter1);
                    name = token.substr(pos1+1);
                }
                i ++;
                line.erase(0, pos+delimiter.length());
            }
            isVirtual = (line == "1");
            if (isVirtual == true){
                virtualMethods.push_back(name);
            }

        }
        file.close();
        return virtualMethods;
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

static RuleSet rules(new AbstractFunctionCallFromConstructorRule());
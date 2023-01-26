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
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "oclint/metric/MethodMaxNestingMetric.h"
#include "oclint/metric/MethodNumOfLocalVarsMetric.h"
#include "oclint/util/Thresholds.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class BrainMethodRule : public AbstractASTVisitorRule<BrainMethodRule>
{

public:
    virtual const string name() const override
    {
        return "brain method";
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
            Stmt *stmt = method->getBody();
            if  (stmt == 0 ) {
                continue;
            }
            const int lineCount = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            const int cc = calculateCyclomaticComplexityOfMethod(*method);
            const int maxNesting = (MethodMaxNestingMetric{}).calculateCXX(*method);
            int noav = NOAVCalc(*method, decl);
            float high_CLOC = getCLOCThreshold();
            float high_CC = getCCThreshold();
            if (lineCount > high_CLOC &&  cc > high_CC && maxNesting > BRAIN_METHOD_MAXNESTING && noav > BRAIN_METHOD_NOAV)
            {
                string description = "C++ class has brain method.";
                addViolation(decl, this, description);
            }
        }

        return true;
    }

    float getCLOCThreshold(){
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        int sumOfLength = 0;
        int numOfMethods = 0;
        string delimiter = ";";
        vector<int> allLength;
        // Run over each line in Methods
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==2) {
                    sumOfLength += stoi(token);
                    numOfMethods += 1;
                    allLength.push_back(stoi(token));
                    break;
                    }
                i ++;
                line.erase(0, pos+delimiter.length());
            }
        }
        file.close();
        // Calculate the threshold
        float std, threshold, avg = 0.0;
        int sumForStd = 0;
        if (numOfMethods > 0){
            avg = (static_cast< float >(sumOfLength) / static_cast< float >(numOfMethods));
        }
        for (auto i = allLength.begin() ; i != allLength.end(); ++i){
            sumForStd += pow((*i-avg),2);
        }
        std = sqrt((static_cast< float >(sumForStd))/(static_cast< float >(numOfMethods)));

        threshold = avg + std;
        return threshold;
    }

    float getCCThreshold(){
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        int sumOfCC = 0;
        int numOfMethods = 0;
        string delimiter = ";";
        vector<int> allCC;
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==4) {
                    sumOfCC += stoi(line);
                    numOfMethods += 1;
                    allCC.push_back(stoi(line));
                    break;
                }
                i ++;
                line.erase(0, pos+delimiter.length());
            }


        }
        file.close();
        // Calculate the threshold
        float std, threshold, avg = 0.0;
        int sumForStd = 0;
        if (numOfMethods > 0){
            avg = (static_cast< float >(sumOfCC) / static_cast< float >(numOfMethods));
        }
        for (auto i = allCC.begin() ; i != allCC.end(); ++i){
            sumForStd += pow((*i-avg),2);
        }
        std = sqrt((static_cast< float >(sumForStd))/(static_cast< float >(numOfMethods)));

        threshold = avg + std;
        return threshold;
    }

    int NOAVCalc (FunctionDecl *method, CXXRecordDecl *decl)
    {
        int counter = 0;
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            string field_name  = f->getNameAsString();
            if (hasStringInMethod(method, field_name)){
                counter ++;
            }
        }
        return counter;
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

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}

};

static RuleSet rules(new BrainMethodRule());

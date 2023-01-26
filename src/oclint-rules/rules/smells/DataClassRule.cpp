#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include "oclint/util/ASTUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "oclint/util/Thresholds.h"
#include "clang/Lex/Lexer.h"
#include <regex>
#include "oclint/metric/CyclomaticComplexityMetric.h"



using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;


class DataClassRule : public AbstractASTVisitorRule<DataClassRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "data class";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "Organic Class Smell";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.7";
    }

    virtual const std::string description() const override
    {
        return "A class with too many lines indicates it does too many things "
            "and is hard to read and understand. "
            "It usually contains complicated code, and should be refactored.";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class c
    {

        )rst";
    }

    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        thresholdMapping["LARGE_CLASS"] =
            "The reporting threshold for too many methods, default value is 10.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        int sumOfWmc = 0;
        int numOfClasses = 0;
        string delimiter = ";";
        vector<int> allWmc;
        // Run over each line in Data
        while (getline (file, line)) {
            numOfClasses ++;
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                line.erase(0, pos+delimiter.length());
                i++;
                if (i == 8 ){
                    sumOfWmc += stoi(line);
                    allWmc.push_back(stoi(line));
                }
            }
        }
        file.close();
        // Calculate the threshold
        float std, threshold, avg = 0.0;
        int sumForStd = 0;
        if (numOfClasses > 0){
            avg = (static_cast< float >(sumOfWmc) / static_cast< float >(numOfClasses));
        }
        for (auto i = allWmc.begin() ; i != allWmc.end(); ++i){
            sumForStd += pow((*i-avg),2);
        }
        std = sqrt((static_cast< float >(sumForStd))/(static_cast< float >(numOfClasses)));

        threshold = (avg + std);

        _threshold = RuleConfiguration::intForKey("DATA_CLASS", threshold);

    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        int noam = 0; // Num of public methods that their getter or setter.
        int nopm = 0; // Num of public methods
        int nopa = 0; // Num of public fields
        int wmc = 0; // Sum of  cyclomatic complexity of all methods
        for (auto fun = decl->method_begin() ; fun != decl->method_end() ; fun++ ){
            wmc += calculateCyclomaticComplexityOfMethod(*fun);
            if ((*fun)->getAccess() == clang::AS_public){
                nopm ++;
                if (isGetOrSet(*fun)){
                    noam ++;
                }
            }
        }
        for (auto field = decl->method_begin() ; field != decl->method_end() ; field++ ){
            if ((*field)->getAccess() == clang::AS_public){
                nopa ++;
            }
        }
        float woc = 0.0; // The ratio between methods that they are public and not setter/getter to all public methods
        if(nopm != 0){
            woc = (static_cast< float >(nopm-noam))/(static_cast< float >(nopm));
        }

        bool moreFewPublicComplexityNotHigh = (nopa + noam) > FEW && wmc < _threshold;
        bool manyPublicComplexityNotVeryHigh = (nopa + noam) > MANY && wmc < (_threshold)*1.5;
        bool dataRatherThanServices = woc < ONE_THIRD;

        if ((moreFewPublicComplexityNotHigh || manyPublicComplexityNotVeryHigh) && dataRatherThanServices)
        {
            string description = "C++ class with WOC = " +to_string(woc)+ ", NOPA = "+to_string(nopa)+ ", NOAM = " + to_string(noam) + ", WMC = " + to_string(wmc);
            addViolation(decl, this, description);
        }
        return true;
    }


    bool isGetOrSet(FunctionDecl *func){
        string funcName = func->getNameAsString();
        string set = "set";
        string get = "get";
        if (funcName.rfind(set,0) == 0 || funcName.rfind(get,0) == 0){
            return true;
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

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}

};

static RuleSet rules(new DataClassRule());

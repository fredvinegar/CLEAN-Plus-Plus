#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include <vector>
#include <cmath>
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "oclint/metric/MethodMaxNestingMetric.h"
#include "oclint/metric/MethodNumOfLocalVarsMetric.h"
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

using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;

class LongMethodRule : public AbstractASTVisitorRule<LongMethodRule>
{

public:
    virtual const string name() const override
    {
        return "long method";
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
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            Stmt *stmt = method->getBody();
            if (stmt == 0){
                continue;
            }
            const int lineCount = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            float avg_MLOC = getMLOCThreshold();
            if ((lineCount > LONG_METHOD_THRESHOLD1 &&  lineCount > avg_MLOC) || lineCount > LONG_METHOD_THRESHOLD2)
            {
                string description = "C++ class has long method with " + toString<int>(lineCount) + " lines.";
                addViolation(decl, this, description);
            }
        }

        return true;
    }


    float getMLOCThreshold(){
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Methods");
        string line;
        int sumOfMLOC = 0;
        int numOfMethods = 0;
        string delimiter = ";";
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==2) {
                    sumOfMLOC += stoi(token);
                    numOfMethods += 1;
                    break;
                }
                i ++;
                line.erase(0, pos+delimiter.length());
            }
        }
        file.close();
        // Calculate the threshold
        float  avg = 0.0;
        if (numOfMethods > 0){
            avg = (static_cast< float >(sumOfMLOC) / static_cast< float >(numOfMethods));
        }

        return avg;
    }
};

static RuleSet rules(new LongMethodRule());

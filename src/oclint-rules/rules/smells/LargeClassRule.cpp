#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include "oclint/util/ASTUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace clang;
using namespace oclint;

class LargeClassRule : public AbstractASTVisitorRule<LargeClassRule>
{
private:
    float _threshold;

public:
    virtual const string name() const override
    {
        return "large class";
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
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        int sumOfLines = 0;
        string delimiter = ";";
        vector<int> allLinesNums;
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==3) {
                    allLinesNums.push_back(stoi(token));
                    sumOfLines += stoi(token);
                }
                line.erase(0, pos+delimiter.length());
                i++;
            }
        }
        file.close();
        // Calculate the threshold
        float std, threshold, avg = 0.0;
        int sumForStd = 0;
        int numOfClasses = allLinesNums.size();
        if (numOfClasses > 0){
            avg = (static_cast< float >(sumOfLines) / static_cast< float >(numOfClasses));
        }
        for (auto i = allLinesNums.begin() ; i != allLinesNums.end(); ++i){
            sumForStd += pow((*i-avg),2);
        }
        std = sqrt((static_cast< float >(sumForStd))/(static_cast< float >(numOfClasses)));

        _threshold = (avg + std) * 1.5;
//        _threshold = RuleConfiguration::intForKey("LARGE_CLASS", threshold);

    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        int length = getNumLineOfClass(decl);
//        cout << "class " << decl->getNameAsString() << " length: " << length << " avg: " << _threshold<< endl;
        if (length > _threshold)
        {
            string description = "C++ abstract class with " + toString<int>(length) +
                                 " methods exceeds limit of " + toString<int>(_threshold);
            addViolation(decl, this, description);
        }
        return true;
    }

    int getNumLineOfClass(CXXRecordDecl *decl)
    {
        int numLine = 2;
        numLine += distance(decl->field_begin(), decl->field_end());
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            Stmt *stmt = method->getBody();
            if  (stmt == 0 ) {
                continue;
            }
            const int lineCount = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            numLine += lineCount;
        }
        return numLine;
    }
};

static RuleSet rules(new LargeClassRule());

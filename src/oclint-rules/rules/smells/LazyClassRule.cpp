#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace clang;
using namespace oclint;

class LazyClassRule : public AbstractASTVisitorRule<LazyClassRule>
{
private:
    int _threshold;

public:
    virtual const string name() const override
    {
        return "lazy class";
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
        return "0.6";
    }

    virtual const std::string description() const override
    {
        return "All classes having LOCs lower than the first quartile of the distribution of LOCs for all system’s classes.";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class Foo
    {
        void bar()
        {
            // 1001 lines of code
        }
    }
        )rst";
    }

    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        thresholdMapping["LAZY_CLASS"] =
            "The class size reporting threshold, default value is 1000.";
        return thresholdMapping;
    }
#endif

    virtual void setUp() override
    {
        // Open the Data file
        std::ifstream file;
        file.open("/tmp/Data");
        string line;
        string delimiter = ";";
        vector<int> allLineNums;
        // Run over each line in Data
        while (getline (file, line)) {
            int i = 1;
            size_t pos = 0;
            string token;
            // For each line take the relevance tokens
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                if (i==3) {
                    allLineNums.push_back(stoi(line));
                }
                line.erase(0, pos+delimiter.length());
                i++;
            }
        }
        file.close();
        // Calculate the threshold
        sort(allLineNums.begin(),allLineNums.end());
        int quartilePos = (allLineNums.size() / 4) ;
        int threshold = allLineNums[quartilePos];
        _threshold = RuleConfiguration::intForKey("LAZY_CLASS", threshold);
    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl)
    {
        int length = getNumLineOfClass(decl);
        if (length < _threshold)
        {
            string description =  "C++ class with " +
                                 toString<int>(length) + " lines below the threshold of " + toString<int>(_threshold);
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

static RuleSet rules(new LazyClassRule());

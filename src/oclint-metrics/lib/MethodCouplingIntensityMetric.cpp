#include "oclint/metric/MethodCouplingIntensityMetric.h"
#include <iostream>
#include <list>
#include "oclint/metric/StringInMethodMetric.h"
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
using namespace oclint;

int MethodCouplingIntensityMetric::couplingIntensityCalc(CXXMethodDecl *decl, list<string> methods_list)
{
    for (auto method = methods_list.begin(); method != methods_list.end(); method++){
        int count;
        if ((StringInMethodMetric{}).hasStringInMethod(decl, *method)){
            count ++;
        }
    }
    return count;
}
// check if its work/
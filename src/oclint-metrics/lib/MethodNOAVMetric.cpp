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
#include "oclint/metric/MethodNOAVMetric.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
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

int MethodNOAVMetric::NOAVCalc (FunctionDecl *method, CXXRecordDecl *decl)
{
    int counter = 0;
    for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
        string field_name  = f->getNameAsString();
        if (StringInMethodMetric{}).hasStringInMethod(method, field_name))){
            counter ++;
        }
    }
    return counter;
}
// check if its work/
// check if it's create float
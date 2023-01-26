#ifndef ROBOTICS_METHODCOUPLINGINTENSITYMETRIC_H
#define ROBOTICS_METHODCOUPLINGINTENSITYMETRIC_H
#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <list>
//#include "oclint/RuleSet.h"
//#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
//#include "oclint/util/Thresholds.h"
//#include "oclint/AbstractASTVisitorRule.h"
//#include "oclint/RuleConfiguration.h"
#include <vector>
#include <cmath>
//#include "oclint/util/ASTUtil.h"
//#include "oclint/util/StdUtil.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
//#include "oclint/RuleCarrier.h"

//namespace oclint
using namespace clang;
using namespace oclint;
//{
    class MethodCouplingIntensityMetric : public clang::RecursiveASTVisitor<MethodCouplingIntensityMetric>
    {

    public:
        int couplingIntensityCalc (CXXMethodDecl *decl, list<string> methods_list);

    };
//}
#endif //ROBOTICS_METHODCOUPLINGINTENSITYMETRIC_H

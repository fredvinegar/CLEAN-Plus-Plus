#ifndef ROBOTICS_METHODNOAVMETRIC_H
#define ROBOTICS_METHODNOAVMETRIC_H
#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <list>
#include "oclint/RuleSet.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include "oclint/util/Thresholds.h"
#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include <vector>
#include <cmath>
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"

//namespace oclint
using namespace clang;
using namespace oclint;

//{
    class MethodNOAVMetric : public clang::RecursiveASTVisitor<MethodNOAVMetric>
    {

    public:
        int NOAVCalc (FunctionDecl *method, CXXRecordDecl *decl);

    };

#endif //ROBOTICS_METHODNOAVMETRIC_H

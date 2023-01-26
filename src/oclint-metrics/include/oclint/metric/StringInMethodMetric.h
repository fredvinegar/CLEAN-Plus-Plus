#ifndef ROBOTICS_STRINGINMETHODMETRIC_H
#define ROBOTICS_STRINGINMETHODMETRIC_H
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

using namespace oclint;
using namespace std;
using namespace clang;


    int count;

    class StringInMethodMetric : public clang::RecursiveASTVisitor<StringInMethodMetric>
    {

    public:
        bool hasStringInMethod (FunctionDecl *decl, string str);
        int countStringInMethod (FunctionDecl *decl, string str);
    };


#endif //ROBOTICS_STRINGINMETHODMETRIC_H

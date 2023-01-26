#include <iostream>
#include "oclint/metric/AbstractClassMethodDeclarationCount.h"
#include "oclint/util/ASTUtil2.h"

using namespace oclint;

int AbstractClassMethodDeclarationCount::count(clang::CXXRecordDecl *decl)
{
    counter = 0;
    TraverseDecl(decl);
    return counter;
}

bool AbstractClassMethodDeclarationCount::VisitFunctionDecl(clang::CXXMethodDecl *decl)
{
    this.counter ++ ;

    return true;
}
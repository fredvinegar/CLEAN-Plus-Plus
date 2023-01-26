#ifndef ROBOTICS_METHODCOUPLINGDISPERSIONMETRIC_H
#define ROBOTICS_METHODCOUPLINGDISPERSIONMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <list>

//namespace oclint
using namespace std;
using namespace clang;
using namespace oclint;
//{
    class MethodCouplingDispersionMetric : public clang::RecursiveASTVisitor<MethodCouplingDispersionMetric>
    {

    public:
        float couplingDispersionCalc (CXXMethodDecl *decl, list<string> methods_list);

    };
//}
#endif //ROBOTICS_METHODCOUPLINGDISPERSIONMETRIC_H

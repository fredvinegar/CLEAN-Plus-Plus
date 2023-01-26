//
// Created by User on 10/26/2022.
//

#ifndef ROBOTICS_METHODNUMBEROFACCESSEDVARMETRIC_H
#define ROBOTICS_METHODNUMBEROFACCESSEDVARMETRIC_H
#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
    class MethodNumOfAccessedVarMetric : public clang::RecursiveASTVisitor<MethodNumOfAccessedVarMetric>
    {
    private:
        int count;

    public:
        int calculate(clang::FunctionDecl *decl);

    };
}
#endif //ROBOTICS_METHODNUMBEROFACCESSEDVARMETRIC_H

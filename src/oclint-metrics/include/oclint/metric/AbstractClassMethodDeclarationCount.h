#ifndef ROBOTICS_ABSTRACTCLASSMETHODDECLARATIONCOUNT_H
#define ROBOTICS_ABSTRACTCLASSMETHODDECLARATIONCOUNT_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
    class AbstractClassMethodDeclarationCount : public clang::RecursiveASTVisitor<AbstractClassMethodDeclarationCount>
    {
    private:
        int counter;

    public:

        int count(clang::CXXRecordDecl*);

        bool VisitFunctionDecl(clang::CXXMethodDecl* decl);
    };
}



#endif //ROBOTICS_ABSTRACTCLASSMETHODDECLARATIONCOUNT_H

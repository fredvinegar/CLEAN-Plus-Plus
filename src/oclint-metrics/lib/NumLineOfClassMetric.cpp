#include "oclint/metric/NumLineOfClassMetric.h"

using namespace clang;

int NumLineOfClass::calculate(clang::Decl *decl)
{
    int numLine = 1;
    numLine += distance(decl->field_begin(), decl->field_end());
    for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
        Stmt *stmt = method->getBody();
        numLine += getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
    }
    return numLine;
}

extern "C" int getNumLineOfClass(clang::Decl *decl)
{
    NumLineOfClass nlocMetric;
    return nlocMetric.calculate(decl);
}

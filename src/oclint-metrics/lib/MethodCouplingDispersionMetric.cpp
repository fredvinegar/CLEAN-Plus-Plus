#include "oclint/metric/MethodCouplingDispersionMetric.h"
#include <iostream>
#include <list>
#include "oclint/metric/StringInMethodMetric.h"

using namespace std;
using namespace oclint;

float MethodCouplingDispersionMetric::couplingDispersionCalc(CXXMethodDecl *decl, list<string> methods_list)
{
    int CINT = (MethodCouplingIntensityMetric{}).couplingDispersionCalc(decl, methods_list);
    int count;
    for (auto method = methods_list.begin(); method != methods_list.end(); method++){
        int count;
        if ((StringInMethodMetric{}).countStringInMethod(decl, *method)){
            count ++;
        }
    }
    return static_cast< float >(count)/static_cast< float >(CINT);
}
// check if its work/
// check if it's create float
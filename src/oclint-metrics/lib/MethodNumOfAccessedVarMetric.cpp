#include "oclint/metric/MethodNumOfAccessedVarMetric.h"
#include <iostream>
#include <list>
#include "oclint/metric/StringInMethodMetric.h"

using namespace std;
using namespace oclint;

int MethodNumOfAccessedVarMetric::calculate(clang::FunctionDecl *decl, list<string> field_list)
{
    for (auto field = field_list.begin(); field != field_list.end(); field++){
        if ((StringInMethodMetric{}).hasStringInMethod(decl, *field)){
            this->count ++;
        }
    }
    return this->count;
}
// check if its work/
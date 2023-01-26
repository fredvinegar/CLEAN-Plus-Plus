// The class has max nesting bigger than 1 but CINT lower than 8 and CDISP higher than 0.25 and .
// -> Has intensive coupling smell.
#include "NotIntensiveCouplingTest2.h"
int NotIntensiveCouplingTest2 :: func1N2(){
    int v1 = this->func2N2();
    int v2 = this->func3N2();
    int v3 = this->func4N2();
    int v4 = this->func5N2();
    int v5 = this->func6N2();
    int v6 = this->func4N2();
    int v7 = this->func5N2();
    int v8 = this->func6N2();

    for (int i=0; i < 10; i++){
        if (i<5){
            v1 --;
        }
        v1 ++;
    }
}
int NotIntensiveCouplingTest2 :: func2N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func3N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func4N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func5N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func6N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func7N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func8N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func9N2(){
    return 0;
}
int NotIntensiveCouplingTest2 :: func10N2(){
    return 0;
}
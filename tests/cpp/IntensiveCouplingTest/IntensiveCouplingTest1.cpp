// The class has CINT larger than 8 and max nesting bigger than 1.
// -> Has intensive coupling smell.
#include "IntensiveCouplingTest1.h"
int IntensiveCouplingTest1 :: func1(){
    int v1 = this->func2();
    int v2 = this->func3();
    int v3 = this->func4();
    int v4 = this->func5();
    int v5 = this->func6();
    int v6 = this->func7();
    int v7 = this->func8();
    int v8 = this->func9();
    int v9 = this->func10();
    for (int i=0; i < 10; i++){
        if (i<5){
            v1 --;
        }
        v1 ++;
    }
}
int IntensiveCouplingTest1 :: func2(){
    return 0;
}
int IntensiveCouplingTest1 :: func3(){
    return 0;
}
int IntensiveCouplingTest1 :: func4(){
    return 0;
}
int IntensiveCouplingTest1 :: func5(){
    return 0;
}
int IntensiveCouplingTest1 :: func6(){
    return 0;
}
int IntensiveCouplingTest1 :: func7(){
    return 0;
}
int IntensiveCouplingTest1 :: func8(){
    return 0;
}
int IntensiveCouplingTest1 :: func9(){
    return 0;
}
int IntensiveCouplingTest1 :: func10(){
    return 0;
}
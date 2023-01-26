// The class has CDISP larger than 0.5 and max nesting bigger than 1 but CINT lower or equal than 8.
// -> Has no dispersed coupling smell.

#include "NotDispersedCouplingTest1.h"
int NotDispersedCouplingTest1 :: func1N1(){
    int v1 = this->func2N1();
    int v2 = this->func3N1();
    int v3 = this->func4N1();
    int v4 = this->func5N1();
    int v5 = this->func6N1();
    int v6 = this->func7N1();
    int v7 = this->func8N1();
    int v8 = this->func9N1();
    for (int i=0; i < 10; i++){
        if (i<5){
            v1 --;
        }
        v1 ++;
    }
}
int NotDispersedCouplingTest1 :: func2N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func3N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func4N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func5N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func6N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func7N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func8N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func9N1(){
    return 0;
}
int NotDispersedCouplingTest1 :: func10N1(){
    return 0;
}
// The class has CINT larger than 8 and CDISP larger than 0.5 and max nesting bigger than 1.
// -> Has dispersed coupling smell.

#include "DispersedCouplingTest.h"
int DispersedCouplingTest :: func1(){
    AnotherClass anotherClass = AnotherClass();
    anotherClass.func1A1();
    anotherClass.func1A1();
    anotherClass.func2A1();
    anotherClass.func3A1();
    anotherClass.func4A1();
    anotherClass.func3A1();
    anotherClass.func4A1();
    int v1 = this->func2();
    for (int i=0; i < 10; i++){
        if (i<5){
            v1 --;
        }
        v1 ++;
    }
}
int DispersedCouplingTest :: func2(){
    return 0;
}
int DispersedCouplingTest :: func3(){
    return 0;
}
int DispersedCouplingTest :: func4(){
    return 0;
}
int DispersedCouplingTest :: func5(){
    return 0;
}
int DispersedCouplingTest :: func6(){
    return 0;
}
int DispersedCouplingTest :: func7(){
    return 0;
}
int DispersedCouplingTest :: func8(){
    return 0;
}
int DispersedCouplingTest :: func9(){
    return 0;
}
int DispersedCouplingTest :: func10(){
    return 0;
}
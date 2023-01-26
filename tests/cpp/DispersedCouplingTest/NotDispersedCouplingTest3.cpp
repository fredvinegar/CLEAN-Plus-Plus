// The class has CINT larger than 8 and CDISP larger than 0.5 but max nesting lower or equal to 1.
// -> Has no dispersed coupling smell.
#include "NotDispersedCouplingTest3.h"
int NotDispersedCouplingTest3 :: func1N3(){
    int v1 = this->func2N3();
    int v2 = this->func3N3();
    int v3 = this->func4N3();
    int v4 = this->func5N3();
    int v5 = this->func6N3();
    int v6 = this->func7N3();
    int v7 = this->func8N3();
    int v8 = this->func9N3();
    int v9 = this->func10N3();

    for (int i=0; i < 10; i++){
        v1 ++;
    }
}
int NotDispersedCouplingTest3 :: func2N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func3N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func4N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func5N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func6N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func7N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func8N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func9N3(){
    return 0;
}
int NotDispersedCouplingTest3 :: func10N3(){
    return 0;
}
// The class has CINT larger than 8 but max nesting lower than 2.
// -> Has no intensive coupling smell.
#include "NotIntensiveCouplingTest1.h"
int NotIntensiveCouplingTest1 :: func1N1(){
    int v1 = this->func2N1();
    int v2 = this->func3N1();
    int v3 = this->func4N1();
    int v4 = this->func5N1();
    int v5 = this->func6N1();
    int v6 = this->func7N1();
    int v7 = this->func8N1();
    int v8 = this->func9N1();
    int v9 = this->func10N1();
    for (int i=0; i < 10; i++){
            v1 --;
    }
}
int NotIntensiveCouplingTest1 :: func2N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func3N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func4N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func5N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func6N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func7N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func8N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func9N1(){
    return 0;
}
int NotIntensiveCouplingTest1 :: func10N1(){
    return 0;
}
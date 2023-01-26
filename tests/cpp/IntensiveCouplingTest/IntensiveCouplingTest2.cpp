// The class has CDISP lower than 0.25 and max nesting bigger than 1.
// -> Has intensive coupling smell.
#include "IntensiveCouplingTest2.h"
int IntensiveCouplingTest2 :: func1T2(){
    int v1 = this->func2T2();
    int v2 = this->func2T2();
    int v3 = this->func2T2();
    int v4 = this->func2T2();
    int v5 = this->func2T2();
    int v6 = this->func2T2();
    switch (v1) {
        case 1:
            v2++;
        case 2:
             while (true){
                 break;
             }
    }
        v1 ++;
}
int IntensiveCouplingTest2 :: func2T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func3T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func4T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func5T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func6T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func7T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func8T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func9T2(){
    return 0;
}
int IntensiveCouplingTest2 :: func10T2(){
    return 0;
}
// The class is abstract and 3 other classes inherit from it.
// -> Has not speculative generality smell.
#include "NotSpeculativeGeneralityTest.h"

void ChildClass1 :: func(){
        int v = 0;
}

void ChildClass2 :: func(){
        int v = 1;
    }

void ChildClass3 :: func(){
        int v = 2;
    }

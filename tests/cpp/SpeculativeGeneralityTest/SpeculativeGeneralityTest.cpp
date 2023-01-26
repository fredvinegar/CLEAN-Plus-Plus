// The class is abstract and less than 3 other classes inherit from it.
// -> Has speculative generality smell.
#include "SpeculativeGeneralityTest.h"
void ChildClass1 :: func(){
        int v = 0;
    }

void ChildClass2 :: func(){
        int v = 1;
    }

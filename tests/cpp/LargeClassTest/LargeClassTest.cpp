// The class having LOC higher than the (average+std)*1.5 of all the classes in the project.
// -> Has large class smell.
#include "LargeClassTest.h"

void LargeClassTest :: func1(int p1){
        this->f1 = p1;
        this->f2 = p1*p1;
        this->f3 = p1+p1;
}
void LargeClassTest :: func2(int p2){
        this->f1 = p2;
        this->f2 = p2*p2;
        this->f3 = p2+p2;
}

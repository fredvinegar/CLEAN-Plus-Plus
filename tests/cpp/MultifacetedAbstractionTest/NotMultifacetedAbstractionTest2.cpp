// The class has LCOM higher than 0.8, and has more than 6 methods, but less than 7 fields.
// -> Has not multifaceted abstraction smell.
#include "NotMultifacetedAbstractionTest2.h"

void NotMultifacetedAbstractionTest2 :: func1() {
    int v = this->f1;
}
void NotMultifacetedAbstractionTest2 :: func2() {
    this->func1();
}
void NotMultifacetedAbstractionTest2 :: func3() {
    int v = this->f1;
}
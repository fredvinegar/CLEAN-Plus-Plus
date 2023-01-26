// The class has more than 6 fields and more than 6 methods, but LCOM lower than 0.8.
// -> Has not multifaceted abstraction smell.
#include "NotMultifacetedAbstractionTest3.h"

void NotMultifacetedAbstractionTest3 :: func1() {
    int v = this->f1;
}
void NotMultifacetedAbstractionTest3 :: func2() {
    this->func1();
}
void NotMultifacetedAbstractionTest3 :: func3() {
    int v = this->f1;
}
void NotMultifacetedAbstractionTest3 :: func4() {
    this->func1();
}
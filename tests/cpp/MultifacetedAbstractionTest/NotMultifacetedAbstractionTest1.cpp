// The class has LCOM higher than 0.8, and has more than 6 fields, but less than 7 methods.
// -> Has not multifaceted abstraction smell.
#include "NotMultifacetedAbstractionTest1.h"

void NotMultifacetedAbstractionTest1 :: func1() {
    this->func2();
}
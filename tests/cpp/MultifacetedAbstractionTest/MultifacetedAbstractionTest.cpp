// The class has LCOM higher than 0.8, and has more than 6 fields and more than 6 methods.
// -> Has multifaceted abstraction smell.
#include "MultifacetedAbstractionTest.h"

void MultifacetedAbstractionTest :: func1a() {
    int v = this->f1a;
}
void MultifacetedAbstractionTest :: func2a() {
    this->func1a();
}
void MultifacetedAbstractionTest :: func3a() {
    int v = this->f1a;
}
// The class having LOCs lower than the first quartile of the distribution of LOCs for all system’s classes.
// -> Has message chain smell.
#include "MessageChainTest.h"

AnotherClass& AnotherClass :: func1(int p) {
    return *this;
}
AnotherClass& AnotherClass :: func2() {
    return *this;
}
AnotherClass & AnotherClass :: func3() {
    return *this;
}
AnotherClass & AnotherClass :: func4() {
    return *this;
}

void MessageChainTest :: func1() {
    int v = 1;
    AnotherClass anotherClass = AnotherClass();
    anotherClass.func1(v).func2().func3().func4();
}
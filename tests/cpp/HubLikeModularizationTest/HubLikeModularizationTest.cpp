// The class calls to 20 other classes or more and 20 other classes or more call it.
// -> Has hub like modularization smell.
#include "HubLikeModularizationTest.h"

void HubLikeModularizationTest :: func1() {
    ClassOut11 classOut11 = ClassOut11();
    ClassOut12 classOut12 = ClassOut12();
    ClassOut13 classOut13 = ClassOut13();
    ClassOut14 classOut14 = ClassOut14();
    ClassOut15 classOut15 = ClassOut15();
    ClassOut16 classOut16 = ClassOut16();
    ClassOut17 classOut17 = ClassOut17();
    ClassOut18 classOut18 = ClassOut18();
    ClassOut19 classOut19 = ClassOut19();
    ClassOut20 classOut20 = ClassOut20();
}
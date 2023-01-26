// The class doesn't have method that has at least one if-else IE where: #(Expression(IE)) >= 3.
// -> Has not complex conditional smell.
#include "NotComplexConditionalTest.h"
void NotComplexConditionalTest :: func1(int p1, int p2, int p3) {
        if (p1 > p3 && p1 > p2) {
            p1 = 0;
        }
}
void NotComplexConditionalTest :: func2(int p1, int p2, int p3) {
        if (p1 > p3 || p1 > p2) {
            p1 = 0;
        }
    }
void NotComplexConditionalTest :: func3(int p1, int p2) {
        if (p1 > p2) {
            p1 = 0;
        }
    }
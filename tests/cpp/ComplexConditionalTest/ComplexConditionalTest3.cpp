// The class has method that has at least one if-else IE where: #(Expression(IE)) >= 3 (example with "and" and "or").
// -> Has complex conditional smell.
#include "ComplexConditionalTest3.h"
void ComplexConditionalTest3 :: func(int p1, int p2, int p3, int p4) {
        if (p1 > p4 && p1 > p2 || p1 > p3) {
            p1 = 0;
        }
}

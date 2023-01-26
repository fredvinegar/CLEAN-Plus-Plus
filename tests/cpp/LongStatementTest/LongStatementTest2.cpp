// The class has method that contain statement longer than 120 (if statement).
// -> Has long statement smell.
#include "LongStatementTest2.h"

void LongStatementTest2 :: fun1(int p1, int p2, int p3) {
    if (this->f1 > p1) {
        this->f1++;
    } else if (this->f1 > p2) {
        this->f1--;
    } else if (this->f1 > p3) {
        this->f1 = this->f2;
    } else {
        this->f1 = 0;
    }
}

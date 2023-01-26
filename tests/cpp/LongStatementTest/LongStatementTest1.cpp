// The class has method that contain statement longer than 120 (declaration statement).
// -> Has long statement smell.
#include "LongStatementTest1.h"

int LongStatementTest1 :: fun1(int veryLongParameter1, int veryLongParameter2, int veryLongParameter3) {
    int veryLongVariable =
            this->veryLongField1 + this->veryLongField2 + veryLongParameter1 + veryLongParameter2 + veryLongParameter3;
    return veryLongVariable;
}
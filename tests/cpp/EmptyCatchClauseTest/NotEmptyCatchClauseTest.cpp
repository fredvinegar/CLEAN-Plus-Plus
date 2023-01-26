// The class has try-catch statement and the catch is not empty
// -> Has not empty catch smell.
#include "NotEmptyCatchClauseTest.h"

void NotEmptyCatchClauseTest :: func1(int p) {
    try {
        if (this->f > p) {
            this->f++;
        } else {
            throw (p);
        }
    }
    catch (int e) {
        this->f--;
    }
}
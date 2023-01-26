// The class has method that has switch case statement with default.
// -> Has missing default smell.
#include "NotMissingDefaultTest.h"

void NotMissingDefaultTest :: fun(int p) {
    switch (p) {
        case 1:
            p++;
        case 2:
            p--;
        case 3:
            p = 0;
        default:
            p = 1;
    }
}
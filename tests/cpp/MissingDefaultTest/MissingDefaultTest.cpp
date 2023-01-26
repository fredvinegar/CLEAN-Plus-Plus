// The class has method that has switch case statement without default.
// -> Has missing default smell.
#include "MissingDefaultTest.h"

void MissingDefaultTest :: fun(int p) {
    switch (p) {
        case 1:
            p++;
        case 2:
            p--;
        case 3:
            p = 0;
    }
}
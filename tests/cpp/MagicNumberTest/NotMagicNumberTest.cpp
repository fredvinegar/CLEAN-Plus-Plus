// The class has magic number that is float.
// -> Has not magic number smell.
#include "NotMagicNumberTest.h"
void NotMagicNumberTest :: func(int p) {
    float v1 = 0.0;
    float v2 = 1.000;
    int v3 = 1;
    int v4 = 0;
    int v5 = 0b1;
    int v6 = 0b0;
    int v7 = 0x1;
    int v8 = 0x0;
    int v9[2] = {12, 45};
}
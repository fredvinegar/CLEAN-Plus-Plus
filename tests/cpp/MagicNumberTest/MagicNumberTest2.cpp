// The class has magic number in if statement.
// -> Has magic number smell.
#include "MagicNumberTest2.h"

void MagicNumberTest2 :: func(int p) {
    if (p < 12) {
        p++;
    }
}
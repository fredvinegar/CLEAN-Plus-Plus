// The class has method that calls to a field with a name longer than 30.
// -> Has long identifier smell.
#include "LongIdentifierTest2.h"

void LongIdentifierTest2 :: fun1(int p) {
    int v = this->thisIsAVeryVeryVeryLongFieldName;
}
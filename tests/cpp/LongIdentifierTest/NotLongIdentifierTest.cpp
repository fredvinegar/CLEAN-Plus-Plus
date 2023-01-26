// The class hasn't method that declare a variable with a name longer than 30,
// or has parameter with a name longer than 30, or calls to a field with a name longer than 30.
// -> Has not long identifier smell.
#include "NotLongIdentifierTest.h"

void NotLongIdentifierTest :: fun1(int thisIsShortParameterName) {
    int thisIsShortVariableName = this->thisIsShortFieldName;
}
// The class having num of public getters/setters and fields higher than 6 (but lower than 7),
// and cyclomatic complexity lower than the (average+std)*1.5 of the project, but the ratio between
// the methods that they are public and not setter/getter to all public methods is higher than 0.33.
// -> Has data class smell.
#include "NotDataClassTest3.h"

int NotDataClassTest3 :: get_f1(){
        return this->f1;
}
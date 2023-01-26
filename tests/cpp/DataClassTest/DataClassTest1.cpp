// The class having num of public getters/setters and fields higher than 4 (but lower than 7),
// and cyclomatic complexity lower than the average+std of the project, and the ratio between
// the methods that they are public and not setter/getter to all public methods is lower than 0.33.
// -> Has data class smell.
#include "DataClassTest1.h"
int DataClassTest1 :: get_f1(){
        return this->f1;
}
int DataClassTest1 :: get_f2(){
        return this->f2;
}
void DataClassTest1 :: set_f2(int p){
        this->f2 = p;
}
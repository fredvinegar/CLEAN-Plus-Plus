// The class having num of public getters/setters and fields lower than 4
// -> Has data class smell.
#include "NotDataClassTest1.h"

int NotDataClassTest1 :: get_f1(){
        return this->f1;
}
void NotDataClassTest1 :: set_f1(int p){
        this->f1 = p;
}

// The class has no inheritance from another class and there is no calls to it.
// -> Has unutilized abstraction smell.
#include "UnutilizedAbstractionTest1.h"

int UnutilizedAbstractionTest1 :: u1fun1(){
    NotUnutilizedAbstractionTest2 notUnutilizedAbstractionTest2;
};
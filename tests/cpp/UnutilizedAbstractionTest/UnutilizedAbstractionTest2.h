#ifndef ROBOTICS_UNUTILIZEDABSTRACTIONTEST2_H
#define ROBOTICS_UNUTILIZEDABSTRACTIONTEST2_H
#include "NotUnutilizedAbstractionTest1.h"
class SuperClass1{
    int s1f1;
    NotUnutilizedAbstractionTest1 notUnutilizedAbstractionTest1;
    void s1fun1(){}
};

class SuperClass2{
    int s2f1;
    void s2fun1(){}
};

class UnutilizedAbstractionTest2: public SuperClass1, public SuperClass2{
    int u2f1;
};



#endif //ROBOTICS_UNUTILIZEDABSTRACTIONTEST2_H

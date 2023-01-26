#ifndef ROBOTICS_NOTREFUSEDBEQUESTTEST_H
#define ROBOTICS_NOTREFUSEDBEQUESTTEST_H
class SuperClass2{
    virtual void func1(){}
    virtual void func2(){}
    virtual void func3(){}
};

class  NotRefusedBequestTest: public SuperClass2{
    void func1(){}
};

#endif //ROBOTICS_NOTREFUSEDBEQUESTTEST_H

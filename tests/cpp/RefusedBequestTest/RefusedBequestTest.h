#ifndef ROBOTICS_REFUSEDBEQUESTTEST_H
#define ROBOTICS_REFUSEDBEQUESTTEST_H
class SuperClass1{
    virtual void func1(){}
    virtual void func2(){}
    virtual void func3(){}
};

class  RefusedBequestTest: public SuperClass1{
    void func1(){}
    void func2(){}
};
#endif //ROBOTICS_REFUSEDBEQUESTTEST_H

#ifndef ROBOTICS_SPECULATIVEGENERALITYTEST_H
#define ROBOTICS_SPECULATIVEGENERALITYTEST_H
class SpeculativeGeneralityTest{
    virtual void func() =0;
};

class ChildClass1 : public SpeculativeGeneralityTest{
    void func();
};

class ChildClass2 : public SpeculativeGeneralityTest{
    void func();
};
#endif //ROBOTICS_SPECULATIVEGENERALITYTEST_H

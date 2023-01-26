#ifndef ROBOTICS_NOTSPECULATIVEGENERALITYTEST_H
#define ROBOTICS_NOTSPECULATIVEGENERALITYTEST_H
class NotSpeculativeGeneralityTest{
    virtual void func() =0;
};

class ChildClass1 : public NotSpeculativeGeneralityTest{
    void func();
};

class ChildClass2 : public NotSpeculativeGeneralityTest{
    void func();
};

class ChildClass3 : public NotSpeculativeGeneralityTest{
    void func();

};
#endif //ROBOTICS_NOTSPECULATIVEGENERALITYTEST_H

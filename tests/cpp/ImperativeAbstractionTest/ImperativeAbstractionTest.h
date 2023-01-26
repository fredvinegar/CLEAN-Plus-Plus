#ifndef ROBOTICS_IMPERATIVEABSTRACTIONTEST_H
#define ROBOTICS_IMPERATIVEABSTRACTIONTEST_H
// The class has exactly 1 public method and this method is over 50 lines
// -> Has imperative abstraction smell.
class ImperativeAbstractionTest{
public:
    int func1();
private:
    void func2(){}
};
#endif //ROBOTICS_IMPERATIVEABSTRACTIONTEST_H

// The constructor of the class call to methods that are not abstract (from the class and from another class).
// -> Has not abstract function call from constructor smell.
#include "NotAbstractFunctionCallFromConstructorTest.h"
NotAbstractFunctionCallFromConstructorTest :: NotAbstractFunctionCallFromConstructorTest(){
        func2();
        AnotherClass1{}.func1();
}


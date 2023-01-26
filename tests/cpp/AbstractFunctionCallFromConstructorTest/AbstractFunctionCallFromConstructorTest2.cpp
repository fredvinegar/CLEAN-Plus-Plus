// The constructor of the class call to at least one abstract method (from another class).
// -> Has abstract function call from constructor smell.
#include "AbstractFunctionCallFromConstructorTest2.h"
AbstractFunctionCallFromConstructorTest2 ::  AbstractFunctionCallFromConstructorTest2(){
        AnotherClass{}.func();
    }



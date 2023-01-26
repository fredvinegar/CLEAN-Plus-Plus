// The constructor of the class call to at least one abstract method (from the same class).
// -> Has abstract function call from constructor smell.
#include "AbstractFunctionCallFromConstructorTest1.h"
AbstractFunctionCallFromConstructorTest1 :: AbstractFunctionCallFromConstructorTest1(){
    this->func();
}
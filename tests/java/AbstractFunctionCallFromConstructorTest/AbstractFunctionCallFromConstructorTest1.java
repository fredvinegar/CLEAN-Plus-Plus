// The constructor of the class call to at least one abstract method (from the same class).
// -> Has abstract function call from constructor smell.
public class AbstractFunctionCallFromConstructorTest1 //Type originates from: AbstractFunctionCallFromConstructorTest1.h
{
	private AbstractFunctionCallFromConstructorTest1() //Method definition originates from: AbstractFunctionCallFromConstructorTest1.cpp
	{
		this.func();
	}

	private void func()
	{
	}
}

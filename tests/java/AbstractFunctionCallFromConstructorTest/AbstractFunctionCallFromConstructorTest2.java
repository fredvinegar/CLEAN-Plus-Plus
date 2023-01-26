// The constructor of the class call to at least one abstract method (from another class).
// -> Has abstract function call from constructor smell.
public class AnotherClass //Type originates from: AbstractFunctionCallFromConstructorTest2.h
{
	public void func()
	{
	}
}

public class AbstractFunctionCallFromConstructorTest2 //Type originates from: AbstractFunctionCallFromConstructorTest2.h
{
	private AbstractFunctionCallFromConstructorTest2() //Method definition originates from: AbstractFunctionCallFromConstructorTest2.cpp
	{
			AnotherClass
			{
			}
			.func();
	}
}



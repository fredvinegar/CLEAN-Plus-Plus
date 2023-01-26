// The constructor of the class call to methods that are not abstract (from the class and from another class).
// -> Has not abstract function call from constructor smell.
public class AnotherClass1 //Type originates from: NotAbstractFunctionCallFromConstructorTest.h
{
	public final void func1()
	{
	}
}

public class NotAbstractFunctionCallFromConstructorTest //Type originates from: NotAbstractFunctionCallFromConstructorTest.h
{
	public NotAbstractFunctionCallFromConstructorTest() //Method definition originates from: NotAbstractFunctionCallFromConstructorTest.cpp
	{
			func2();
			AnotherClass1
			{
			}
			.func1();
	}

	public final void func2()
	{
	}
}


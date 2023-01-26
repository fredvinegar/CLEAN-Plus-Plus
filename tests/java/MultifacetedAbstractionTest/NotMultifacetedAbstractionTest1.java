// The class has LCOM higher than 0.8, and has more than 6 fields, but less than 7 methods.
// -> Has not multifaceted abstraction smell.
public class NotMultifacetedAbstractionTest1 //Type originates from: NotMultifacetedAbstractionTest1.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private int f7;
	private void func1() //Method definition originates from: NotMultifacetedAbstractionTest1.cpp
	{
		this.func2();
	}

	private void func2()
	{
	}
	private void func3()
	{
	}
	private void func4()
	{
	}
	private void func5()
	{
	}
	private void func6()
	{
	}

}

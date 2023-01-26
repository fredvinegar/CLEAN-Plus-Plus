// The class has LCOM higher than 0.8, and has more than 6 methods, but less than 7 fields.
// -> Has not multifaceted abstraction smell.
public class NotMultifacetedAbstractionTest2 //Type originates from: NotMultifacetedAbstractionTest2.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private void func1() //Method definition originates from: NotMultifacetedAbstractionTest2.cpp
	{
		int v = this.f1;
	}

	private void func2() //Method definition originates from: NotMultifacetedAbstractionTest2.cpp
	{
		this.func1();
	}

	private void func3() //Method definition originates from: NotMultifacetedAbstractionTest2.cpp
	{
		int v = this.f1;
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
	private void func7()
	{
	}
	private void func8()
	{
	}
	private void func9()
	{
	}
	private void func10()
	{
	}

}

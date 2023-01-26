// The class has more than 6 fields and more than 6 methods, but LCOM lower than 0.8.
// -> Has not multifaceted abstraction smell.
public class NotMultifacetedAbstractionTest3 //Type originates from: NotMultifacetedAbstractionTest3.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private int f7;
	private void func1() //Method definition originates from: NotMultifacetedAbstractionTest3.cpp
	{
		int v = this.f1;
	}

	private void func2() //Method definition originates from: NotMultifacetedAbstractionTest3.cpp
	{
		this.func1();
	}

	private void func3() //Method definition originates from: NotMultifacetedAbstractionTest3.cpp
	{
		int v = this.f1;
	}

	private void func4() //Method definition originates from: NotMultifacetedAbstractionTest3.cpp
	{
		this.func1();
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

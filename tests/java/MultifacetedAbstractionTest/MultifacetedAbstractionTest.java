// The class has LCOM higher than 0.8, and has more than 6 fields and more than 6 methods.
// -> Has multifaceted abstraction smell.
public class MultifacetedAbstractionTest //Type originates from: MultifacetedAbstractionTest.h
{
	private int f1a;
	private int f2a;
	private int f3a;
	private int f4a;
	private int f5a;
	private int f6a;
	private int f7a;
	private void func1a() //Method definition originates from: MultifacetedAbstractionTest.cpp
	{
		int v = this.f1a;
	}

	private void func2a() //Method definition originates from: MultifacetedAbstractionTest.cpp
	{
		this.func1a();
	}

	private void func3a() //Method definition originates from: MultifacetedAbstractionTest.cpp
	{
		int v = this.f1a;
	}

	private void func4a()
	{
	}
	private void func5a()
	{
	}
	private void func6a()
	{
	}
	private void func7a()
	{
	}
	private void func8a()
	{
	}
	private void func9a()
	{
	}
	private void func10a()
	{
	}

}

// The class has CINT larger than 8 and CDISP larger than 0.5 and max nesting bigger than 1.
// -> Has dispersed coupling smell.

public class DispersedCouplingTest //Type originates from: DispersedCouplingTest.h
{
	private int f1;
	private int f2;
	private int func1() //Method definition originates from: DispersedCouplingTest.cpp
	{
		AnotherClass anotherClass = new AnotherClass();
		anotherClass.func1A1();
		anotherClass.func1A1();
		anotherClass.func2A1();
		anotherClass.func3A1();
		anotherClass.func4A1();
		anotherClass.func3A1();
		anotherClass.func4A1();
		int v1 = this.func2();
		for (int i = 0; i < 10; i++)
		{
			if (i < 5)
			{
				v1--;
			}
			v1++;
		}
	}

	private int func2() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func3() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func4() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func5() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func6() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func7() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func8() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func9() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}

	private int func10() //Method definition originates from: DispersedCouplingTest.cpp
	{
		return 0;
	}
}

public class AnotherClass //Type originates from: DispersedCouplingTest.h
{
	public final void func1A1()
	{
	}
	public final void func2A1()
	{
	}
	public final void func3A1()
	{
	}
	public final void func4A1()
	{
	}
	public final void func5A1()
	{
	}
	public final void func6A1()
	{
	}
	public final void func7A1()
	{
	}
	public final void func8A1()
	{
	}
	public final void func9A1()
	{
	}
	public final void func10A1()
	{
	}
}

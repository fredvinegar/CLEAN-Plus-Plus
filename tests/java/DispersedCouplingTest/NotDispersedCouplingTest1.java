// The class has CDISP larger than 0.5 and max nesting bigger than 1 but CINT lower or equal than 8.
// -> Has no dispersed coupling smell.

public class NotDispersedCouplingTest1 //Type originates from: NotDispersedCouplingTest1.h
{
	private int f1;
	private int f2;
	private int func1N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		int v1 = this.func2N1();
		int v2 = this.func3N1();
		int v3 = this.func4N1();
		int v4 = this.func5N1();
		int v5 = this.func6N1();
		int v6 = this.func7N1();
		int v7 = this.func8N1();
		int v8 = this.func9N1();
		for (int i = 0; i < 10; i++)
		{
			if (i < 5)
			{
				v1--;
			}
			v1++;
		}
	}

	private int func2N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func3N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func4N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func5N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func6N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func7N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func8N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func9N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}

	private int func10N1() //Method definition originates from: NotDispersedCouplingTest1.cpp
	{
		return 0;
	}
}

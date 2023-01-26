// The class has CINT larger than 8 and CDISP larger than 0.5 but max nesting lower or equal to 1.
// -> Has no dispersed coupling smell.


public class NotDispersedCouplingTest3 //Type originates from: NotDispersedCouplingTest3.h
{
	private int f1;
	private int f2;
	private int func1N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		int v1 = this.func2N3();
		int v2 = this.func3N3();
		int v3 = this.func4N3();
		int v4 = this.func5N3();
		int v5 = this.func6N3();
		int v6 = this.func7N3();
		int v7 = this.func8N3();
		int v8 = this.func9N3();
		int v9 = this.func10N3();

		for (int i = 0; i < 10; i++)
		{
			v1++;
		}
	}

	private int func2N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func3N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func4N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func5N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func6N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func7N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func8N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func9N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}

	private int func10N3() //Method definition originates from: NotDispersedCouplingTest3.cpp
	{
		return 0;
	}
}

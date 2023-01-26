// The class has CINT larger than 8 and max nesting bigger than 1 but CDISP lower or equal to 0.5 .
// -> Has no dispersed coupling smell.

public class NotDispersedCouplingTest2 //Type originates from: NotDispersedCouplingTest2.h
{
	private int f1;
	private int f2;
	private int func1N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		int v1 = this.func2N2();
		int v2 = this.func3N2();
		int v3 = this.func4N2();
		int v4 = this.func5N2();
		int v5 = this.func6N2();
		int v6 = this.func7N2();
		int v7 = this.func8N2();
		int v8 = this.func9N2();
		int v9 = this.func10N2();
		int v11 = this.func2N2();
		int v12 = this.func3N2();
		int v13 = this.func4N2();
		int v14 = this.func5N2();
		int v15 = this.func6N2();
		int v16 = this.func7N2();
		int v17 = this.func8N2();
		int v18 = this.func9N2();
		int v19 = this.func10N2();
		for (int i = 0; i < 10; i++)
		{
			if (i < 5)
			{
				v1--;
			}
			v1++;
		}
	}

	private int func2N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func3N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func4N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func5N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func6N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func7N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func8N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func9N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}

	private int func10N2() //Method definition originates from: NotDispersedCouplingTest2.cpp
	{
		return 0;
	}
}

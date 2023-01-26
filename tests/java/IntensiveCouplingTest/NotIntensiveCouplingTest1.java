// The class has CINT larger than 8 but max nesting lower than 2.
// -> Has no intensive coupling smell.


public class NotIntensiveCouplingTest1 //Type originates from: NotIntensiveCouplingTest1.h
{
	private int f1;
	private int f2;
	private int func1() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		int v1 = this.func2();
		int v2 = this.func3();
		int v3 = this.func4();
		int v4 = this.func5();
		int v5 = this.func6();
		int v6 = this.func7();
		int v7 = this.func8();
		int v8 = this.func9();
		int v9 = this.func10();
		for (int i = 0; i < 10; i++)
		{
				v1--;
		}
	}

	private int func2() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func3() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func4() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func5() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func6() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func7() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func8() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func9() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}

	private int func10() //Method definition originates from: NotIntensiveCouplingTest1.cpp
	{
		return 0;
	}
}

// The class has CDISP lower than 0.25 and max nesting bigger than 1.
// -> Has intensive coupling smell.


public class IntensiveCouplingTest2 //Type originates from: IntensiveCouplingTest2.h
{
	private int f1;
	private int f2;
	private int func1() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		int v1 = this.func2();
		int v2 = this.func2();
		int v3 = this.func2();
		int v4 = this.func2();
		int v5 = this.func2();
		int v6 = this.func2();
		switch (v1)
		{
			case 1:
				v2++;
			case 2:
				 while (true)
				 {
					 break;
				 }
		}
			v1++;
	}

	private int func2() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func3() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func4() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func5() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func6() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func7() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func8() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func9() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}

	private int func10() //Method definition originates from: IntensiveCouplingTest2.cpp
	{
		return 0;
	}
}

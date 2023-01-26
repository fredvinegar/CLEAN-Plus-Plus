// The class has MLOC larger than the average+std of all methods and cc larger the average+std of all methods and NOAV larger than 6 and max nesting lower or equal to 5.
// -> Has no brain method smell.



public class NotBrainMethodTest1 //Type originates from: NotBrainMethodTest1.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private int f7;
	private void N1func1() //Method definition originates from: NotBrainMethodTest1.cpp
	{
		int v1 = this.f1;
		int v2 = this.f2;
		int v3 = this.f3;
		int v4 = this.f4;
		int v5 = this.f5;
		for (int i = 0; i < 10; i++)
		{
			if (this.f7 < 5)
			{
				v1--;
				switch (this.f6)
				{
					case 1:
						v1++;
					case 2:
						while (true)
						{
							break;
						}
				}
			}
		}
	}

	private void N1func2()
	{
	}
	private void N1func3()
	{
	}
	private void N1func4()
	{
	}
	private void N1func5()
	{
	}
	private void N1func6()
	{
	}
	private void N1func7()
	{
	}
	private void N1func8()
	{
	}
	private void N1func9()
	{
	}
	private void N1func10()
	{
	}
}

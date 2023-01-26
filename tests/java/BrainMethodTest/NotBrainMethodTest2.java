// The class has MLOC larger than the average+std of all methods and cc larger the average+std of all methods and max nesting bigger than 5 but NOAV lower or equal to 6.
// -> Has no brain method smell.


public class NotBrainMethodTest2 //Type originates from: NotBrainMethodTest2.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private int f7;
	private void N2func1() //Method definition originates from: NotBrainMethodTest2.cpp
	{
		int v1 = this.f1;
		int v2 = this.f2;
		int v3 = this.f3;
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
							try
							{
								if (true)
								{
									break;
								}
							}
							catch (java.lang.Exception e)
							{
								if (true)
								{
									v1--;
								}
							}

						}
				}
			}
		}
	}

	private void N2func2()
	{
	}
	private void N2func3()
	{
	}
	private void N2func4()
	{
	}
	private void N2func5()
	{
	}
	private void N2func6()
	{
	}
	private void N2func7()
	{
	}
	private void N2func8()
	{
	}
	private void N2func9()
	{
	}
	private void N2func10()
	{
	}
}

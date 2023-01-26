// The class has MLOC larger than the average+std of all methods and cc larger the average+std of all methods and NOAV larger than 6 and max nesting bigger than 5.
// -> Has brain method smell.


public class BrainMethodTest //Type originates from: BrainMethodTest.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private int f6;
	private int f7;
	private void func1() //Method definition originates from: BrainMethodTest.cpp
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

	private void func2()
	{
	}
	private void func3()
	{
	}
	private void func4()
	{
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

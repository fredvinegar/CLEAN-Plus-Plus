// The class doesn't have a method that has cyclomatic complexity bigger or equal to 8.
// -> Has complex methodTest smell.
public class NotComplexMethodTest //Type originates from: NotComplexMethodTest.h
{
	private void fun1(int p1, int p2, int p3) //Method definition originates from: NotComplexMethodTest.cpp
	{
		/*if
		 * else
		 * while
		 * case
		 * for*/
		int v = 0;
		while (true)
		{
			v++;
			break;
		}
		//  for (int i=0; i < 10; i++)
		for (int i = 0; i < 10; i++)
		{
			if (i < 5)
			{
				p1--;
			}
			p1++;
		}


		switch (p3)
		{
			case 1:
				p3++;
			case 2:
				p3--;
			default:
				p3 = 0;
		}

	}

	private void fun2(int p1, int p2, int p3) //Method definition originates from: NotComplexMethodTest.cpp
	{
			try
			{
				if (p1 < 0)
				{
					throw (0);
				}
			}
			catch (int i)
			{
				p3 = i;
			}
	}
}

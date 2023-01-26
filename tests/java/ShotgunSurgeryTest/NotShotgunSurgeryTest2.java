// The class has method that 8 or more other functions call it, but has cyclomatic complexity lower than 6.
// -> Has shotgun surgery smell.
public class NotShotgunSurgeryTest2 //Type originates from: NotShotgunSurgeryTest2.h
{
	private void Not2fun1(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < 5)
			{
				p1--;
			}
			p1++;
		}
		int v = 0;
		while (true)
		{
			v++;
			break;
		}

	}

	private void Not2fun2(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun3(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun4(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun5(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun6(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun7(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun8(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun9(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}

	private void Not2fun10(int p1, int p2, int p3) //Method definition originates from: NotShotgunSurgeryTest2.cpp
	{
		this.Not2fun1(p1, p2, p3);
	}
}

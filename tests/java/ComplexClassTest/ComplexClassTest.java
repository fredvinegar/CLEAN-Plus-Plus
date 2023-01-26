import java.io.*;

// The class has method with cyclomatic complexity higher than 10 that it is nor a constructor nor destructor.
// -> Has complex class smell.
public class ComplexClassTest implements Closeable //Type originates from: ComplexClassTest.h
{
	private int v;
	private ComplexClassTest(int p) //Method definition originates from: ComplexClassTest.cpp
	{
		this.v = p;
	}

	private void func(int p1, int p2, int p3) //Method definition originates from: ComplexClassTest.cpp
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
		while (true)
		{
			v++;
			break;
		}
		while (true)
		{
			v++;
			break;
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
		switch (p3)
		{
			case 1:
				p3++;
			case 2:
				p3--;
			default:
				p3 = 0;
		}
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

	public final void close() //Method definition originates from: ComplexClassTest.cpp
	{
		this.v--;
	}
}

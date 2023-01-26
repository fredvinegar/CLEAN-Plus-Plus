import java.io.*;

// The class doesn't have constructor or destructor with cyclomatic complexity higher than 10.
// -> Has not complex class smell.
public class NotComplexClassTest implements Closeable //Type originates from: NotComplexClassTest.h
{
	private NotComplexClassTest(int p1, int p2, int p3) //Method definition originates from: NotComplexClassTest.cpp
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


	}

	private void func1(int p1) //Method definition originates from: NotComplexClassTest.cpp
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

	public final void close() //Method definition originates from: NotComplexClassTest.cpp
	{
			int p1 = 1;
			int p2 = 1;
			int p3 = 1;
			for (int i = 0; i < 10; i++)
			{
				if (i < 5)
				{
					p1--;
				}
				p1++;
			}
			int v = 0;
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
}

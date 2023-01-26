// The class has method that has switch case statement without default.
// -> Has missing default smell.
public class MissingDefaultTest //Type originates from: MissingDefaultTest.h
{
	private void fun(int p) //Method definition originates from: MissingDefaultTest.cpp
	{
		switch (p)
		{
			case 1:
				p++;
			case 2:
				p--;
			case 3:
				p = 0;
		}
	}
}

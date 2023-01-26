// The class has method that has switch case statement with default.
// -> Has missing default smell.
public class NotMissingDefaultTest //Type originates from: NotMissingDefaultTest.h
{
	private void fun(int p) //Method definition originates from: NotMissingDefaultTest.cpp
	{
		switch (p)
		{
			case 1:
				p++;
			case 2:
				p--;
			case 3:
				p = 0;
			default:
				p = 1;
		}
	}
}

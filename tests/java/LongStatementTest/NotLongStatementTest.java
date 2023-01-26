// The class doesn't have method that contain statement longer than 120.
// -> Has not long statement smell.
public class NotLongStatementTest //Type originates from: NotLongStatementTest.h
{
	private int f1;
	private int f2;
	private int fun1(int p1, int p2, int p3) //Method definition originates from: NotLongStatementTest.cpp
	{
		if (this.f1 > p1)
		{
			this.f1++;
		}
		else
		{
			this.f1 = 0;
		}
		int v = this.f1 + this.f2;
		return v;
	}
}

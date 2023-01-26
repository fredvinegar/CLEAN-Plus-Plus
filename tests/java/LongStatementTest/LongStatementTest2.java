// The class has method that contain statement longer than 120 (if statement).
// -> Has long statement smell.
public class LongStatementTest2 //Type originates from: LongStatementTest2.h
{
	private int f1;
	private int f2;
	private void fun1(int p1, int p2, int p3) //Method definition originates from: LongStatementTest2.cpp
	{
		if (this.f1 > p1)
		{
			this.f1++;
		}
		else if (this.f1 > p2)
		{
			this.f1--;
		}
		else if (this.f1 > p3)
		{
			this.f1 = this.f2;
		}
		else
		{
			this.f1 = 0;
		}
	}

}

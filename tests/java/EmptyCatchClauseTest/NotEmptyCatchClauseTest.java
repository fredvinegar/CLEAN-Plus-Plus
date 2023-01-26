// The class has try-catch statement and the catch is not empty
// -> Has not empty catch smell.
public class NotEmptyCatchClauseTest //Type originates from: NotEmptyCatchClauseTest.h
{
	private int f;
	private void func1(int p) //Method definition originates from: NotEmptyCatchClauseTest.cpp
	{
		try
		{
			if (this.f > p)
			{
				this.f++;
			}
			else
			{
				throw (p);
			}
		}
		catch (int e)
		{
			this.f--;
		}
	}
}

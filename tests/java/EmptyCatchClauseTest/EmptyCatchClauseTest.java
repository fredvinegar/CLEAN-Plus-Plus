// The class has try-catch statement and the catch is empty
// -> Has empty catch smell.
public class EmptyCatchClauseTest //Type originates from: EmptyCatchClauseTest.h
{
	private int f;
	private void func1(int p) //Method definition originates from: EmptyCatchClauseTest.cpp
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

			}
	}
}

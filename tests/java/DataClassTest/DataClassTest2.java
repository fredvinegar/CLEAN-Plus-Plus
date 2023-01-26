// The class having num of public getters/setters and fields higher than 6,
// and cyclomatic complexity lower than the (average+std)*1.5 of the project, and the ratio between
// the methods that they are public and not setter/getter to all public methods is lower than 0.33.
// -> Has data class smell.
public class DataClassTest2 //Type originates from: DataClassTest2.h
{
	public int f1;
	public int f2;
	public int f3;
	public final int get_f1() //Method definition originates from: DataClassTest2.cpp
	{
			for (int i = 0; i < 5; i++)
			{
				if (i == 4)
				{
					break;
				}
				else
				{
					this.f2--;
				}
			}
			while (this.f1 != 0)
			{
				if (this.f1 < 5)
				{
					break;
				}
				else
				{
					break;
				}
			}
			for (int i = 0; i < 5; i++)
			{
				if (i == 4)
				{
					break;
				}
				else
				{
					this.f2--;
				}
			}
			while (this.f1 != 0)
			{
				if (this.f1 < 5)
				{
					break;
				}
				else
				{
					break;
				}
			}
			try
			{
				if (this.f1 < 0)
				{
					throw (0);
				}
			}
			catch (int i)
			{
			}
			switch (this.f1)
			{
				case 1:
					this.f1++;
				case 2:
					this.f1--;
				default:
					this.f1 = 0;
			}
			return this.f1;
	}

	public final int get_f2() //Method definition originates from: DataClassTest2.cpp
	{
			return this.f2;
	}

	public final void set_f1(int p) //Method definition originates from: DataClassTest2.cpp
	{
			this.f1 = p;
	}

	public final void set_f2(int p) //Method definition originates from: DataClassTest2.cpp
	{
			this.f2 = p;
	}

	public final void func1()
	{
	}

}

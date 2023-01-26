// The class having num of public getters/setters and fields higher than 6,
// but cyclomatic complexity higher than the (average+std)*1.5 of the project.
// -> Has data class smell.
public class NotDataClassTest2 //Type originates from: NotDataClassTest2.h
{
	public int f1;
	public int f2;
	public int f3;

	public final int get_f1() //Method definition originates from: NotDataClassTest2.cpp
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

	public final int get_f2() //Method definition originates from: NotDataClassTest2.cpp
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
			return this.f2;
	}

	public final void set_f1(int p) //Method definition originates from: NotDataClassTest2.cpp
	{
			this.f1 = p;
	}

	public final void set_f2(int p) //Method definition originates from: NotDataClassTest2.cpp
	{
			this.f2 = p;
	}

}

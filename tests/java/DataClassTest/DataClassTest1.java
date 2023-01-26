// The class having num of public getters/setters and fields higher than 4 (but lower than 7),
// and cyclomatic complexity lower than the average+std of the project, and the ratio between
// the methods that they are public and not setter/getter to all public methods is lower than 0.33.
// -> Has data class smell.
public class DataClassTest1 //Type originates from: DataClassTest1.h
{
	public int f1;
	public int f2;
	public final int get_f1() //Method definition originates from: DataClassTest1.cpp
	{
			return this.f1;
	}

	public final int get_f2() //Method definition originates from: DataClassTest1.cpp
	{
			return this.f2;
	}

	public final void set_f2(int p) //Method definition originates from: DataClassTest1.cpp
	{
			this.f2 = p;
	}

}

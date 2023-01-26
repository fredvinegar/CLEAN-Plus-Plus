// The class having num of public getters/setters and fields lower than 4
// -> Has data class smell.
public class NotDataClassTest1 //Type originates from: NotDataClassTest1.h
{
	public int f1;
	public final int get_f1() //Method definition originates from: NotDataClassTest1.cpp
	{
			return this.f1;
	}

	public final void set_f1(int p) //Method definition originates from: NotDataClassTest1.cpp
	{
			this.f1 = p;
	}
}

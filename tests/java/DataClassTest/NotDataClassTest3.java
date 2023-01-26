// The class having num of public getters/setters and fields higher than 6 (but lower than 7),
// and cyclomatic complexity lower than the (average+std)*1.5 of the project, but the ratio between
// the methods that they are public and not setter/getter to all public methods is higher than 0.33.
// -> Has data class smell.
public class NotDataClassTest3 //Type originates from: NotDataClassTest3.h
{
	public int f1;
	public int f2;
	public int f3;
	public final int get_f1() //Method definition originates from: NotDataClassTest3.cpp
	{
			return this.f1;
	}

	public final void func1()
	{
	}
	public final void func2()
	{
	}
	public final void func3()
	{
	}
	public final void func4()
	{
	}
}

public class AnotherClass1 //Type originates from: NotDataClassTest3.h
{

}
public class AnotherClass2 //Type originates from: NotDataClassTest3.h
{

}
public class AnotherClass3 //Type originates from: NotDataClassTest3.h
{

}

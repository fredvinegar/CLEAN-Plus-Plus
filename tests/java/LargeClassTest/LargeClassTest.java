// The class having LOC higher than the (average+std)*1.5 of all the classes in the project.
// -> Has large class smell.
public class LargeClassTest //Type originates from: LargeClassTest.h
{
	private int f1;
	private int f2;
	private int f3;
	private int f4;
	private int f5;
	private void func1(int p1) //Method definition originates from: LargeClassTest.cpp
	{
			this.f1 = p1;
			this.f2 = p1 * p1;
			this.f3 = p1 + p1;
	}

	private void func2(int p2) //Method definition originates from: LargeClassTest.cpp
	{
			this.f1 = p2;
			this.f2 = p2 * p2;
			this.f3 = p2 + p2;
	}
}

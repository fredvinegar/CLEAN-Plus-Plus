// The class has no inheritance from another class and there is no calls to it.
// -> Has unutilized abstraction smell.

public class UnutilizedAbstractionTest1 //Type originates from: UnutilizedAbstractionTest1.h
{
	private SuperClass3 superClass3 = new SuperClass3();
	private int u1f2;
	private int u1fun1() //Method definition originates from: UnutilizedAbstractionTest1.cpp
	{
		NotUnutilizedAbstractionTest2 notUnutilizedAbstractionTest2 = new NotUnutilizedAbstractionTest2();
	}
}

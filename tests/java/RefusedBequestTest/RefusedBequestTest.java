// The class override more than half of it's super class methods.
// -> Has refused bequestTest smell.
public class SuperClass1 //Type originates from: RefusedBequestTest.h
{
	private void func1()
	{
	}
	private void func2()
	{
	}
	private void func3()
	{
	}
}

public class RefusedBequestTest extends SuperClass1 //Type originates from: RefusedBequestTest.h
{
	private void func1()
	{
	}
	private void func2()
	{
	}
}


// The class override less than half of it's super class methods.
// -> Has not refused bequestTest smell.
public class SuperClass2 //Type originates from: NotRefusedBequestTest.h
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

public class NotRefusedBequestTest extends SuperClass2 //Type originates from: NotRefusedBequestTest.h
{
	private void func1()
	{
	}
}


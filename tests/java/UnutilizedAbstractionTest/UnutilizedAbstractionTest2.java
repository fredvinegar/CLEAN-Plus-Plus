// The class inheritance from another class this class not called from another classes.
// -> Has unutilized abstraction smell.

public class SuperClass1 //Type originates from: UnutilizedAbstractionTest2.h
{
	private int s1f1;
	private NotUnutilizedAbstractionTest1 notUnutilizedAbstractionTest1 = new NotUnutilizedAbstractionTest1();
	private void s1fun1()
	{
	}
}

public class SuperClass2 //Type originates from: UnutilizedAbstractionTest2.h
{
	private int s2f1;
	private void s2fun1()
	{
	}
}

//C++ TO JAVA CONVERTER TASK: Multiple inheritance is not available in Java:
public class UnutilizedAbstractionTest2 extends SuperClass1, SuperClass2 //Type originates from: UnutilizedAbstractionTest2.h
{
	private int u2f1;
}





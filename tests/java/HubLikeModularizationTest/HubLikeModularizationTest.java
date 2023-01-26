// The class calls to 20 other classes or more and 20 other classes or more call it.
// -> Has hub like modularization smell.
public class ClassOut1 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut2 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut3 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut4 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut5 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut6 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut7 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut8 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut9 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut10 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut11 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut12 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut13 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut14 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut15 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut16 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut17 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut18 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut19 //Type originates from: HubLikeModularizationTest.h
{
}
public class ClassOut20 //Type originates from: HubLikeModularizationTest.h
{
}

public class HubLikeModularizationTest //Type originates from: HubLikeModularizationTest.h
{
	private ClassOut1 classOut1 = new ClassOut1();
	private ClassOut2 classOut2 = new ClassOut2();
	private ClassOut3 classOut3 = new ClassOut3();
	private ClassOut4 classOut4 = new ClassOut4();
	private ClassOut5 classOut5 = new ClassOut5();
	private ClassOut6 classOut6 = new ClassOut6();
	private ClassOut7 classOut7 = new ClassOut7();
	private ClassOut8 classOut8 = new ClassOut8();
	private ClassOut9 classOut9 = new ClassOut9();
	private ClassOut10 classOut10 = new ClassOut10();
	private void func1() //Method definition originates from: HubLikeModularizationTest.cpp
	{
		ClassOut11 classOut11 = new ClassOut11();
		ClassOut12 classOut12 = new ClassOut12();
		ClassOut13 classOut13 = new ClassOut13();
		ClassOut14 classOut14 = new ClassOut14();
		ClassOut15 classOut15 = new ClassOut15();
		ClassOut16 classOut16 = new ClassOut16();
		ClassOut17 classOut17 = new ClassOut17();
		ClassOut18 classOut18 = new ClassOut18();
		ClassOut19 classOut19 = new ClassOut19();
		ClassOut20 classOut20 = new ClassOut20();
	}
}

public class ClassIn1 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn2 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn3 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn4 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn5 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn6 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn7 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn8 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn9 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn10 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn11 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn12 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn13 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn14 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn15 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn16 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn17 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn18 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn19 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}
public class ClassIn20 //Type originates from: HubLikeModularizationTest.h
{
	private HubLikeModularizationTest hubLikeModularizationTest = new HubLikeModularizationTest();
}

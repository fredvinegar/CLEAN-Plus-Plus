// The class is abstract and 3 other classes inherit from it.
// -> Has not speculative generality smell.
public interface NotSpeculativeGeneralityTest //Type originates from: NotSpeculativeGeneralityTest.h
{
	void func();
}

public class ChildClass1 implements NotSpeculativeGeneralityTest //Type originates from: NotSpeculativeGeneralityTest.h
{
	private void func() //Method definition originates from: NotSpeculativeGeneralityTest.cpp
	{
			int v = 0;
	}
}

public class ChildClass2 implements NotSpeculativeGeneralityTest //Type originates from: NotSpeculativeGeneralityTest.h
{
	private void func() //Method definition originates from: NotSpeculativeGeneralityTest.cpp
	{
			int v = 1;
	}
}

public class ChildClass3 implements NotSpeculativeGeneralityTest //Type originates from: NotSpeculativeGeneralityTest.h
{
	private void func() //Method definition originates from: NotSpeculativeGeneralityTest.cpp
	{
			int v = 2;
	}

}

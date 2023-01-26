// The class is abstract and less than 3 other classes inherit from it.
// -> Has speculative generality smell.
public interface SpeculativeGeneralityTest //Type originates from: SpeculativeGeneralityTest.h
{
	void func();
}

public class ChildClass1 implements SpeculativeGeneralityTest //Type originates from: SpeculativeGeneralityTest.h
{
	private void func() //Method definition originates from: SpeculativeGeneralityTest.cpp
	{
			int v = 0;
	}
}

public class ChildClass2 implements SpeculativeGeneralityTest //Type originates from: SpeculativeGeneralityTest.h
{
	private void func() //Method definition originates from: SpeculativeGeneralityTest.cpp
	{
			int v = 1;
	}
}

// The class having LOCs lower than the first quartile of the distribution of LOCs for all system's classes.
// -> Has message chain smell.
public class AnotherClass //Type originates from: NotMessageChainTest.h
{
	public final AnotherClass func1(int p) //Method definition originates from: NotMessageChainTest.cpp
	{
		return this;
	}

	public final AnotherClass func2() //Method definition originates from: NotMessageChainTest.cpp
	{
		return this;
	}

	public final AnotherClass func3() //Method definition originates from: NotMessageChainTest.cpp
	{
		return this;
	}

	public final AnotherClass func4() //Method definition originates from: NotMessageChainTest.cpp
	{
		return this;
	}
}

public class NotMessageChainTest //Type originates from: NotMessageChainTest.h
{
	private void func1() //Method definition originates from: NotMessageChainTest.cpp
	{
		int v = 1;
		AnotherClass anotherClass = new AnotherClass();
		anotherClass.func1(v).func2().func3();
	}
}

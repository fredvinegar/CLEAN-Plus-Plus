// The class has method that has parameter with a name longer than 30.
// -> Has long identifier smell.
public class LongIdentifierTest1 //Type originates from: LongIdentifierTest1.h
{
	private int f;
	private void fun1(int thisIsAVeryVeryVeryLongParameterName) //Method definition originates from: LongIdentifierTest1.cpp
	{
		int v = this.f;
	}
}

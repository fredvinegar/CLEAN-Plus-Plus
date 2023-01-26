// The class has method that declare a variable with a name longer than 30.
// -> Has long identifier smell.
public class LongIdentifierTest3 //Type originates from: LongIdentifierTest3.h
{
	private int f;
	private void fun1(int p) //Method definition originates from: LongIdentifierTest3.cpp
	{
		int thisIsAVeryVeryVeryLongVariableName = this.f;
	}
}

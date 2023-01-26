// The class has method that declare a variable (with few variables in same declaration) with a name longer than 30.
// -> Has long identifier smell.
public class LongIdentifierTest5 //Type originates from: LongIdentifierTest5.h
{
	private int f;
	private void fun1(int p) //Method definition originates from: LongIdentifierTest5.cpp
	{
		int v1;
		int thisIsAVeryVeryVeryLongVariableName;
		int v2;
	}
}

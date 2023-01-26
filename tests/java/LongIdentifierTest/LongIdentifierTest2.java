// The class has method that calls to a field with a name longer than 30.
// -> Has long identifier smell.
public class LongIdentifierTest2 //Type originates from: LongIdentifierTest2.h
{
	private int thisIsAVeryVeryVeryLongFieldName;
	private void fun1(int p) //Method definition originates from: LongIdentifierTest2.cpp
	{
		int v = this.thisIsAVeryVeryVeryLongFieldName;
	}
}

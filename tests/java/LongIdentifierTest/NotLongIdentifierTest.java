// The class hasn't method that declare a variable with a name longer than 30,
// or has parameter with a name longer than 30, or calls to a field with a name longer than 30.
// -> Has not long identifier smell.
public class NotLongIdentifierTest //Type originates from: NotLongIdentifierTest.h
{
	private int thisIsShortFieldName;
	private void fun1(int thisIsShortParameterName) //Method definition originates from: NotLongIdentifierTest.cpp
	{
		int thisIsShortVariableName = this.thisIsShortFieldName;
	}
}

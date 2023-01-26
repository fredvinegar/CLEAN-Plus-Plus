// The class has method that contain statement longer than 120 (declaration statement).
// -> Has long statement smell.
public class LongStatementTest1 //Type originates from: LongStatementTest1.h
{
	private int veryLongField1;
	private int veryLongField2;
	private int fun1(int veryLongParameter1, int veryLongParameter2, int veryLongParameter3) //Method definition originates from: LongStatementTest1.cpp
	{
		int veryLongVariable = this.veryLongField1 + this.veryLongField2 + veryLongParameter1 + veryLongParameter2 + veryLongParameter3;
		return veryLongVariable;
	}

}

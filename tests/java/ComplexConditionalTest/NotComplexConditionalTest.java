// The class doesn't have method that has at least one if-else IE where: #(Expression(IE)) >= 3.
// -> Has not complex conditional smell.
public class NotComplexConditionalTest //Type originates from: NotComplexConditionalTest.h
{
	private void func1(int p1, int p2, int p3) //Method definition originates from: NotComplexConditionalTest.cpp
	{
			if (p1 > p3 && p1 > p2)
			{
				p1 = 0;
			}
	}

	private void func2(int p1, int p2, int p3) //Method definition originates from: NotComplexConditionalTest.cpp
	{
			if (p1 > p3 || p1 > p2)
			{
				p1 = 0;
			}
	}

	private void func3(int p1, int p2) //Method definition originates from: NotComplexConditionalTest.cpp
	{
			if (p1 > p2)
			{
				p1 = 0;
			}
	}
}

// The class has method that has at least one if-else IE where: #(Expression(IE)) >= 3 (example with "and" and "or").
// -> Has complex conditional smell.
public class ComplexConditionalTest3 //Type originates from: ComplexConditionalTest3.h
{
	private void func(int p1, int p2, int p3, int p4) //Method definition originates from: ComplexConditionalTest3.cpp
	{
			if (p1 > p4 && p1 > p2 || p1 > p3)
			{
				p1 = 0;
			}
	}
}

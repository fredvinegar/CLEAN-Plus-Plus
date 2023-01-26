// The class has at least 2 long methods that call to same field. (long method= longer than the average in the class)
// -> Has spaghetti code smell.
public class SpaghettiCodeTest1 //Type originates from: SpaghettiCodeTest1.h
{
	private int f1;
	private void func1() //Method definition originates from: SpaghettiCodeTest1.cpp
	{
			int v = this.f1;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
	}

	private void func2() //Method definition originates from: SpaghettiCodeTest1.cpp
	{
			int v = this.f1;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
			v++;
	}

	private void func3()
	{
	}
	private void func4()
	{
	}
}

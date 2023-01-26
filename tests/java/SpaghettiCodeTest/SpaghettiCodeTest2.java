// The class has at least 2 long methods that call to each other. (long method= longer than the average in the class)
// -> Has spaghetti code smell.
public class SpaghettiCodeTest2 //Type originates from: SpaghettiCodeTest2.h
{
	private int f1;
	private int func1() //Method definition originates from: SpaghettiCodeTest2.cpp
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
			return v;
	}

	private void func2() //Method definition originates from: SpaghettiCodeTest2.cpp
	{
			int v = this.func1();
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

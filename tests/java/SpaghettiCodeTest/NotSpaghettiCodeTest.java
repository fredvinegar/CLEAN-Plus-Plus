// The class doesn't have 2 long methods that call to each other ot fall to the same field.
// -> Has spaghetti code smell.
public class NotSpaghettiCodeTest //Type originates from: NotSpaghettiCodeTest.h
{
	private int f1;
	private int f2;
	private int func1() //Method definition originates from: NotSpaghettiCodeTest.cpp
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

	private void func2() //Method definition originates from: NotSpaghettiCodeTest.cpp
	{
			int v = this.f2;
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

	private void func3() //Method definition originates from: NotSpaghettiCodeTest.cpp
	{
			int v = this.f2;
	}

	private void func4() //Method definition originates from: NotSpaghettiCodeTest.cpp
	{
			this.func2();
	}
}

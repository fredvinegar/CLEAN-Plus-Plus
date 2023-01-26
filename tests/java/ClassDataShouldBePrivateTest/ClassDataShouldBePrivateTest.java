// The class has at least 1 public field.
// -> Has class data should be private smell.
public class ClassDataShouldBePrivateTest //Type originates from: ClassDataShouldBePrivateTest.h
{
	private void fun() //Method definition originates from: ClassDataShouldBePrivateTest.cpp
	{
		int v = 0;
	}

	private int isPrivate;
	public int notPrivate;

}

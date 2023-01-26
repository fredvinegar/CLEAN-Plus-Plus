// The class has magic number in if statement.
// -> Has magic number smell.
public class MagicNumberTest2 //Type originates from: MagicNumberTest2.h
{
	private void func(int p) //Method definition originates from: MagicNumberTest2.cpp
	{
		if (p < 12)
		{
			p++;
		}
	}
}

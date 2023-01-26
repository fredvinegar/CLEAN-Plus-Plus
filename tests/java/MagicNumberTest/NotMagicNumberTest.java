// The class has magic number that is float.
// -> Has not magic number smell.
public class NotMagicNumberTest //Type originates from: NotMagicNumberTest.h
{
	private void func(int p) //Method definition originates from: NotMagicNumberTest.cpp
	{
		float v1 = 0.0F;
		float v2 = 1.000F;
		int v3 = 1;
		int v4 = 0;
		int v5 = 0b1;
		int v6 = 0b0;
		int v7 = 0x1;
		int v8 = 0x0;
		int[] v9 = {12, 45};
	}
}

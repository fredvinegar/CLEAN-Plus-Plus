import java.io.*;

// The class has no inheritance from another class but another class calls to it (from method).
// -> Has unutilized abstraction smell.




public class NotUnutilizedAbstractionTest2 implements Closeable //Type originates from: NotUnutilizedAbstractionTest2.h
{
	public NotUnutilizedAbstractionTest2()
	{
	}
	public final void close()
	{
	}

}




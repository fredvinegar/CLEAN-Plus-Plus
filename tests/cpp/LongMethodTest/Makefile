prog: LongMethodTest1.o LongMethodTest2.o NotLongMethodTest.o
	echo ""

LongMethodTest1.o: LongMethodTest1.cpp LongMethodTest1.h
	g++ -c -Wall LongMethodTest1.cpp -nostartfiles -I.

LongMethodTest2.o: LongMethodTest2.cpp LongMethodTest2.h
	g++ -c -Wall LongMethodTest2.cpp -nostartfiles -I.

NotLongMethodTest.o: NotLongMethodTest.cpp NotLongMethodTest.h
	g++ -c -Wall NotLongMethodTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

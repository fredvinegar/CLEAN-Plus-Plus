prog: LargeClassTest.o NotLargeClassTest.o
	echo ""

LargeClassTest.o: LargeClassTest.cpp LargeClassTest.h
	g++ -c -Wall LargeClassTest.cpp -nostartfiles -I.

NotLargeClassTest.o: NotLargeClassTest.cpp NotLargeClassTest.h
	g++ -c -Wall NotLargeClassTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

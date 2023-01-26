prog: LongIdentifierTest1.o LongIdentifierTest2.o LongIdentifierTest3.o LongIdentifierTest4.o LongIdentifierTest5.o NotLongIdentifierTest.o
	echo ""

LongIdentifierTest1.o: LongIdentifierTest1.cpp LongIdentifierTest1.h
	g++ -c -Wall LongIdentifierTest1.cpp -nostartfiles -I.

LongIdentifierTest2.o: LongIdentifierTest2.cpp LongIdentifierTest2.h
	g++ -c -Wall LongIdentifierTest2.cpp -nostartfiles -I.

LongIdentifierTest3.o: LongIdentifierTest3.cpp LongIdentifierTest3.h
	g++ -c -Wall LongIdentifierTest3.cpp -nostartfiles -I.

LongIdentifierTest4.o: LongIdentifierTest4.cpp LongIdentifierTest4.h
	g++ -c -Wall LongIdentifierTest4.cpp -nostartfiles -I.

LongIdentifierTest5.o: LongIdentifierTest5.cpp LongIdentifierTest5.h
	g++ -c -Wall LongIdentifierTest5.cpp -nostartfiles -I.

NotLongIdentifierTest.o: NotLongIdentifierTest.cpp NotLongIdentifierTest.h
	g++ -c -Wall NotLongIdentifierTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

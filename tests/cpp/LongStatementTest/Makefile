prog: LongStatementTest1.o LongStatementTest2.o NotLongStatementTest.o
	echo ""

LongStatementTest1.o: LongStatementTest1.cpp LongStatementTest1.h
	g++ -c -Wall LongStatementTest1.cpp -nostartfiles -I.

LongStatementTest2.o: LongStatementTest2.cpp LongStatementTest2.h
	g++ -c -Wall LongStatementTest2.cpp -nostartfiles -I.

NotLongStatementTest.o: NotLongStatementTest.cpp NotLongStatementTest.h
	g++ -c -Wall NotLongStatementTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

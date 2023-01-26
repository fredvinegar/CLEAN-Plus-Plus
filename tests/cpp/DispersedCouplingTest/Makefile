prog: DispersedCouplingTest.o NotDispersedCouplingTest1.o NotDispersedCouplingTest2.o NotDispersedCouplingTest3.o
	echo ""

DispersedCouplingTest.o: DispersedCouplingTest.cpp DispersedCouplingTest.h
	g++ -c -Wall DispersedCouplingTest.cpp -nostartfiles -I.

NotDispersedCouplingTest1.o: NotDispersedCouplingTest1.cpp NotDispersedCouplingTest1.h
	g++ -c -Wall NotDispersedCouplingTest1.cpp -nostartfiles -I.

NotDispersedCouplingTest2.o: NotDispersedCouplingTest2.cpp NotDispersedCouplingTest2.h
	g++ -c -Wall NotDispersedCouplingTest2.cpp -nostartfiles -I.

NotDispersedCouplingTest3.o: NotDispersedCouplingTest3.cpp NotDispersedCouplingTest3.h
	g++ -c -Wall NotDispersedCouplingTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

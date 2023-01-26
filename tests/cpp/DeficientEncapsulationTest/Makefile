prog: DeficientEncapsulationTest.o NotDeficientEncapsulationTest.o
	echo ""

DeficientEncapsulationTest.o: DeficientEncapsulationTest.cpp DeficientEncapsulationTest.h
	g++ -c -Wall DeficientEncapsulationTest.cpp -nostartfiles -I.

NotDeficientEncapsulationTest.o: NotDeficientEncapsulationTest.cpp NotDeficientEncapsulationTest.h
	g++ -c -Wall NotDeficientEncapsulationTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

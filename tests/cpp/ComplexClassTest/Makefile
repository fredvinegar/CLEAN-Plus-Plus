prog: ComplexClassTest.o NotComplexClassTest.o
	echo ""

ComplexClassTest.o: ComplexClassTest.cpp ComplexClassTest.h
	g++ -c -Wall ComplexClassTest.cpp -nostartfiles -I.

NotComplexClassTest.o: NotComplexClassTest.cpp NotComplexClassTest.h
	g++ -c -Wall NotComplexClassTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

prog: ComplexMethodTest.o NotComplexMethodTest.o
	echo ""

ComplexMethodTest.o: ComplexMethodTest.cpp ComplexMethodTest.h
	g++ -c -Wall ComplexMethodTest.cpp -nostartfiles -I.

NotComplexMethodTest.o: NotComplexMethodTest.cpp NotComplexMethodTest.h
	g++ -c -Wall NotComplexMethodTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

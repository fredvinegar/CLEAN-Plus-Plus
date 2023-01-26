prog: BrainMethodTest.o NotBrainMethodTest1.o NotBrainMethodTest2.o
	echo ""

BrainMethodTest.o: BrainMethodTest.cpp BrainMethodTest.h
	g++ -c -Wall BrainMethodTest.cpp -nostartfiles -I.

NotBrainMethodTest1.o: NotBrainMethodTest1.cpp NotBrainMethodTest1.h
	g++ -c -Wall NotBrainMethodTest1.cpp -nostartfiles -I.

NotBrainMethodTest2.o: NotBrainMethodTest2.cpp NotBrainMethodTest2.h
	g++ -c -Wall NotBrainMethodTest2.cpp -nostartfiles -I.

clean:
	rm -f *.o

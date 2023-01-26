prog: BrokenModularizationTest.o NotBrokenModularizationTest1.o NotBrokenModularizationTest2.o NotBrokenModularizationTest3.o
	echo ""

BrokenModularizationTest.o: BrokenModularizationTest.cpp BrokenModularizationTest.h
	g++ -c -Wall BrokenModularizationTest.cpp -nostartfiles -I.

NotBrokenModularizationTest1.o: NotBrokenModularizationTest1.cpp NotBrokenModularizationTest1.h
	g++ -c -Wall NotBrokenModularizationTest1.cpp -nostartfiles -I.

NotBrokenModularizationTest2.o: NotBrokenModularizationTest2.cpp NotBrokenModularizationTest2.h
	g++ -c -Wall NotBrokenModularizationTest2.cpp -nostartfiles -I.

NotBrokenModularizationTest3.o: NotBrokenModularizationTest3.cpp NotBrokenModularizationTest3.h
	g++ -c -Wall NotBrokenModularizationTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

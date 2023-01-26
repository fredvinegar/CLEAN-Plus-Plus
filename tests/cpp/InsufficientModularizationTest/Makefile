prog: InsufficientModularizationTest1.o InsufficientModularizationTest2.o InsufficientModularizationTest3.o NotInsufficientModularizationTest.o
	echo ""

InsufficientModularizationTest1.o: InsufficientModularizationTest1.cpp InsufficientModularizationTest1.h
	g++ -c -Wall InsufficientModularizationTest1.cpp -nostartfiles -I.

InsufficientModularizationTest2.o: InsufficientModularizationTest2.cpp InsufficientModularizationTest2.h
	g++ -c -Wall InsufficientModularizationTest2.cpp -nostartfiles -I.

InsufficientModularizationTest3.o: InsufficientModularizationTest3.cpp InsufficientModularizationTest3.h
	g++ -c -Wall InsufficientModularizationTest3.cpp -nostartfiles -I.

NotInsufficientModularizationTest.o: NotInsufficientModularizationTest.cpp NotInsufficientModularizationTest.h
	g++ -c -Wall NotInsufficientModularizationTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

prog: BrainClassTest1.o BrainClassTest2.o NotBrainClassTest1.o NotBrainClassTest2.o NotBrainClassTest3.o
	echo ""

BrainClassTest1.o: BrainClassTest1.cpp BrainClassTest1.h
	g++ -c -Wall BrainClassTest1.cpp -nostartfiles -I.

BrainClassTest2.o: BrainClassTest2.cpp BrainClassTest2.h
	g++ -c -Wall BrainClassTest2.cpp -nostartfiles -I.

NotBrainClassTest1.o: NotBrainClassTest1.cpp NotBrainClassTest1.h
	g++ -c -Wall NotBrainClassTest1.cpp -nostartfiles -I.

NotBrainClassTest2.o: NotBrainClassTest2.cpp NotBrainClassTest2.h
	g++ -c -Wall NotBrainClassTest2.cpp -nostartfiles -I.

NotBrainClassTest3.o: NotBrainClassTest3.cpp NotBrainClassTest3.h
	g++ -c -Wall NotBrainClassTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

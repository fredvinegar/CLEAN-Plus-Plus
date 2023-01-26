prog: UnnecessaryAbstractionTest.o NotUnnecessaryAbstractionTest1.o NotUnnecessaryAbstractionTest2.o NotUnnecessaryAbstractionTest3.o
	echo ""

UnnecessaryAbstractionTest.o: UnnecessaryAbstractionTest.cpp UnnecessaryAbstractionTest.h
	g++ -c -Wall UnnecessaryAbstractionTest.cpp -nostartfiles -I.

NotUnnecessaryAbstractionTest1.o: NotUnnecessaryAbstractionTest1.cpp NotUnnecessaryAbstractionTest1.h
	g++ -c -Wall NotUnnecessaryAbstractionTest1.cpp -nostartfiles -I.

NotUnnecessaryAbstractionTest2.o: NotUnnecessaryAbstractionTest2.cpp NotUnnecessaryAbstractionTest2.h
	g++ -c -Wall NotUnnecessaryAbstractionTest2.cpp -nostartfiles -I.

NotUnnecessaryAbstractionTest3.o: NotUnnecessaryAbstractionTest3.cpp NotUnnecessaryAbstractionTest3.h
	g++ -c -Wall NotUnnecessaryAbstractionTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

prog: ImperativeAbstractionTest.o NotImperativeAbstractionTest1.o NotImperativeAbstractionTest2.o NotImperativeAbstractionTest3.o
	echo ""

ImperativeAbstractionTest.o: ImperativeAbstractionTest.cpp ImperativeAbstractionTest.h
	g++ -c -Wall ImperativeAbstractionTest.cpp -nostartfiles -I.

NotImperativeAbstractionTest1.o: NotImperativeAbstractionTest1.cpp NotImperativeAbstractionTest1.h
	g++ -c -Wall NotImperativeAbstractionTest1.cpp -nostartfiles -I.

NotImperativeAbstractionTest2.o: NotImperativeAbstractionTest2.cpp NotImperativeAbstractionTest2.h
	g++ -c -Wall NotImperativeAbstractionTest2.cpp -nostartfiles -I.

NotImperativeAbstractionTest3.o: NotImperativeAbstractionTest3.cpp NotImperativeAbstractionTest3.h
	g++ -c -Wall NotImperativeAbstractionTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

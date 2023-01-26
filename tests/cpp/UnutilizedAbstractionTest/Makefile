prog: UnutilizedAbstractionTest1.o UnutilizedAbstractionTest2.o NotUnutilizedAbstractionTest1.o NotUnutilizedAbstractionTest2.o NotUnutilizedAbstractionTest3.o
	echo ""

UnutilizedAbstractionTest1.o: UnutilizedAbstractionTest1.cpp UnutilizedAbstractionTest1.h
	g++ -c -Wall UnutilizedAbstractionTest1.cpp -nostartfiles -I.

UnutilizedAbstractionTest2.o: UnutilizedAbstractionTest2.cpp UnutilizedAbstractionTest2.h
	g++ -c -Wall UnutilizedAbstractionTest2.cpp -nostartfiles -I.

NotUnutilizedAbstractionTest1.o: NotUnutilizedAbstractionTest1.cpp NotUnutilizedAbstractionTest1.h
	g++ -c -Wall NotUnutilizedAbstractionTest1.cpp -nostartfiles -I.

NotUnutilizedAbstractionTest2.o: NotUnutilizedAbstractionTest2.cpp NotUnutilizedAbstractionTest2.h
	g++ -c -Wall NotUnutilizedAbstractionTest2.cpp -nostartfiles -I.

NotUnutilizedAbstractionTest3.o: NotUnutilizedAbstractionTest3.cpp NotUnutilizedAbstractionTest3.h
	g++ -c -Wall NotUnutilizedAbstractionTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

prog: ShotgunSurgeryTest.o NotShotgunSurgeryTest1.o NotShotgunSurgeryTest2.o
	echo ""

ShotgunSurgeryTest.o: ShotgunSurgeryTest.cpp ShotgunSurgeryTest.h
	g++ -c -Wall ShotgunSurgeryTest.cpp -nostartfiles -I.

NotShotgunSurgeryTest1.o: NotShotgunSurgeryTest1.cpp NotShotgunSurgeryTest1.h
	g++ -c -Wall NotShotgunSurgeryTest1.cpp -nostartfiles -I.

NotShotgunSurgeryTest2.o: NotShotgunSurgeryTest2.cpp NotShotgunSurgeryTest2.h
	g++ -c -Wall NotShotgunSurgeryTest2.cpp -nostartfiles -I.

clean:
	rm -f *.o

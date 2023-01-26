prog: SwissArmyKnifeTest.o NotSwissArmyKnifeTest1.o NotSwissArmyKnifeTest2.o NotSwissArmyKnifeTest3.o NotSwissArmyKnifeTest4.o NotSwissArmyKnifeTest5.o
	echo ""

SwissArmyKnifeTest1.o: SwissArmyKnifeTest.cpp SwissArmyKnifeTest.h
	g++ -c -Wall SwissArmyKnifeTest1.cpp -nostartfiles -I.

SwissArmyKnifeTest2.o: NotSwissArmyKnifeTest1.cpp NotSwissArmyKnifeTest1.h
	g++ -c -Wall SwissArmyKnifeTest2.cpp -nostartfiles -I.

SwissArmyKnifeTest3.o: NotSwissArmyKnifeTest2.cpp NotSwissArmyKnifeTest2.h
	g++ -c -Wall SwissArmyKnifeTest3.cpp -nostartfiles -I.

SwissArmyKnifeTest4.o: NotSwissArmyKnifeTest3.cpp NotSwissArmyKnifeTest3.h
	g++ -c -Wall SwissArmyKnifeTest4.cpp -nostartfiles -I.

SwissArmyKnifeTest5.o: NotSwissArmyKnifeTest4.cpp NotSwissArmyKnifeTest4.h
	g++ -c -Wall SwissArmyKnifeTest5.cpp -nostartfiles -I.

SwissArmyKnifeTest6.o: NotSwissArmyKnifeTest5.cpp NotSwissArmyKnifeTest5.h
	g++ -c -Wall SwissArmyKnifeTest6.cpp -nostartfiles -I.

clean:
	rm -f *.o

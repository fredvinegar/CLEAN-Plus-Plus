prog: NotClassDataShouldBePrivateTest.o ClassDataShouldBePrivateTest.o
	echo ""

NotClassDataShouldBePrivateTest.o: NotClassDataShouldBePrivateTest.cpp NotClassDataShouldBePrivateTest.h
	g++ -c -Wall NotClassDataShouldBePrivateTest.cpp -nostartfiles -I.

ClassDataShouldBePrivateTest.o: ClassDataShouldBePrivateTest.cpp ClassDataShouldBePrivateTest.h
	g++ -c -Wall ClassDataShouldBePrivateTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

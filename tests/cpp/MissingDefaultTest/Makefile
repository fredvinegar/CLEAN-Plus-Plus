prog: MissingDefaultTest.o NotMissingDefaultTest.o
	echo ""

MissingDefaultTest.o: MissingDefaultTest.cpp MissingDefaultTest.h
	g++ -c -Wall MissingDefaultTest.cpp -nostartfiles -I.

NotMissingDefaultTest.o: NotMissingDefaultTest.cpp NotMissingDefaultTest.h
	g++ -c -Wall NotMissingDefaultTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

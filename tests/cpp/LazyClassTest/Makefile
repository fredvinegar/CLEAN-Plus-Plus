prog: LazyClassTest.o NotLazyClassTest1.o NotLazyClassTest2.o NotLazyClassTest3.o
	echo ""

LazyClassTest.o: LazyClassTest.cpp LazyClassTest.h
	g++ -c -Wall LazyClassTest.cpp -nostartfiles -I.

NotLazyClassTest1.o: NotLazyClassTest1.cpp NotLazyClassTest1.h
	g++ -c -Wall NotLazyClassTest1.cpp -nostartfiles -I.

NotLazyClassTest2.o: NotLazyClassTest2.cpp NotLazyClassTest2.h
	g++ -c -Wall NotLazyClassTest2.cpp -nostartfiles -I.

NotLazyClassTest3.o: NotLazyClassTest3.cpp NotLazyClassTest3.h
	g++ -c -Wall NotLazyClassTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

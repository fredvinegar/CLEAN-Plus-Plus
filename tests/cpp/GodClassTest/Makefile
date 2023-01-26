prog: GodClassTest.o NotGodClassTest1.o NotGodClassTest2.o
	echo ""

GodClassTest.o: GodClassTest.cpp GodClassTest.h
	g++ -c -Wall GodClassTest.cpp -nostartfiles -I.

NotGodClassTest1.o: NotGodClassTest1.cpp NotGodClassTest1.h
	g++ -c -Wall NotGodClassTest1.cpp -nostartfiles -I.

NotGodClassTest2.o: NotGodClassTest2.cpp NotGodClassTest2.h
	g++ -c -Wall NotGodClassTest2.cpp -nostartfiles -I.

clean:
	rm -f *.o

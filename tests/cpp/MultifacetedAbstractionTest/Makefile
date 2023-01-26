prog: MultifacetedAbstractionTest.o NotMultifacetedAbstractionTest1.o NotMultifacetedAbstractionTest2.o NotMultifacetedAbstractionTest3.o
	echo ""

MultifacetedAbstractionTest.o: MultifacetedAbstractionTest.cpp MultifacetedAbstractionTest.h
	g++ -c -Wall MultifacetedAbstractionTest.cpp -nostartfiles -I.

NotMultifacetedAbstractionTest1.o: NotMultifacetedAbstractionTest1.cpp NotMultifacetedAbstractionTest1.h
	g++ -c -Wall NotMultifacetedAbstractionTest1.cpp -nostartfiles -I.

NotMultifacetedAbstractionTest2.o: NotMultifacetedAbstractionTest2.cpp NotMultifacetedAbstractionTest2.h
	g++ -c -Wall NotMultifacetedAbstractionTest2.cpp -nostartfiles -I.

NotMultifacetedAbstractionTest3.o: NotMultifacetedAbstractionTest3.cpp NotMultifacetedAbstractionTest3.h
	g++ -c -Wall NotMultifacetedAbstractionTest3.cpp -nostartfiles -I.

clean:
	rm -f *.o

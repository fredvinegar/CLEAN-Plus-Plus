prog: IntensiveCouplingTest1.o IntensiveCouplingTest2.o NotIntensiveCouplingTest1.o NotIntensiveCouplingTest2.o
	echo ""

IntensiveCouplingTest1.o: IntensiveCouplingTest1.cpp IntensiveCouplingTest1.h
	g++ -c -Wall IntensiveCouplingTest1.cpp -nostartfiles -I.

IntensiveCouplingTest2.o: IntensiveCouplingTest2.cpp IntensiveCouplingTest2.h
	g++ -c -Wall IntensiveCouplingTest2.cpp -nostartfiles -I.

NotIntensiveCouplingTest1.o: NotIntensiveCouplingTest1.cpp NotIntensiveCouplingTest1.h
	g++ -c -Wall NotIntensiveCouplingTest1.cpp -nostartfiles -I.

NotIntensiveCouplingTest2.o: NotIntensiveCouplingTest2.cpp NotIntensiveCouplingTest2.h
	g++ -c -Wall NotIntensiveCouplingTest2.cpp -nostartfiles -I.

clean:
	rm -f *.o

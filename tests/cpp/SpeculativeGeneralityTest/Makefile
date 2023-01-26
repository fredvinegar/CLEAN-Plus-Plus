prog: SpeculativeGeneralityTest.o NotSpeculativeGeneralityTest.o
	echo ""

SpeculativeGeneralityTest.o: SpeculativeGeneralityTest.cpp SpeculativeGeneralityTest.h
	g++ -c -Wall SpeculativeGeneralityTest.cpp -nostartfiles -I.

NotSpeculativeGeneralityTest.o: NotSpeculativeGeneralityTest.cpp NotSpeculativeGeneralityTest.h
	g++ -c -Wall NotSpeculativeGeneralityTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

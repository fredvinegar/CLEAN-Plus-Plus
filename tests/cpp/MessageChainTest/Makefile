prog: MessageChainTest.o NotMessageChainTest.o
	echo ""

MessageChainTest.o: MessageChainTest.cpp MessageChainTest.h
	g++ -c -Wall MessageChainTest.cpp -nostartfiles -I.

NotMessageChainTest.o: NotMessageChainTest.cpp NotMessageChainTest.h
	g++ -c -Wall NotMessageChainTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

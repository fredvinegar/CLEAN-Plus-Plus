prog: HubLikeModularizationTest.o NotHubLikeModularizationTest1.o NotHubLikeModularizationTest2.o
	echo ""

HubLikeModularizationTest.o: HubLikeModularizationTest.cpp HubLikeModularizationTest.h
	g++ -c -Wall HubLikeModularizationTest.cpp -nostartfiles -I.

NotHubLikeModularizationTest1.o: NotHubLikeModularizationTest1.cpp NotHubLikeModularizationTest1.h
	g++ -c -Wall NotHubLikeModularizationTest1.cpp -nostartfiles -I.

NotHubLikeModularizationTest2.o: NotHubLikeModularizationTest2.cpp NotHubLikeModularizationTest2.h
	g++ -c -Wall NotHubLikeModularizationTest2.cpp -nostartfiles -I.

clean:
	rm -f *.o

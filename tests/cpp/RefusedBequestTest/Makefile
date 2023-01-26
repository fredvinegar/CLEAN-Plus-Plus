prog: RefusedBequestTest.o NotRefusedBequestTest.o
	echo ""

RefusedBequestTest.o: RefusedBequestTest.cpp RefusedBequestTest.h
	g++ -c -Wall RefusedBequestTest.cpp -nostartfiles -I.

NotRefusedBequestTest.o: NotRefusedBequestTest.cpp NotRefusedBequestTest.h
	g++ -c -Wall NotRefusedBequestTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

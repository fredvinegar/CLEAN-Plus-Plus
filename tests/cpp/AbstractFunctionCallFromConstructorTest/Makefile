prog: AbstractFunctionCallFromConstructorTest1.o AbstractFunctionCallFromConstructorTest2.o NotAbstractFunctionCallFromConstructorTest.o
	echo ""

AbstractFunctionCallFromConstructorTest1.o: AbstractFunctionCallFromConstructorTest1.cpp AbstractFunctionCallFromConstructorTest1.h
	g++ -c -Wall AbstractFunctionCallFromConstructorTest1.cpp -nostartfiles -I.

AbstractFunctionCallFromConstructorTest1.o: AbstractFunctionCallFromConstructorTest2.cpp AbstractFunctionCallFromConstructorTest2.h
	g++ -c -Wall AbstractFunctionCallFromConstructorTest1.cpp -nostartfiles -I.

NotAbstractFunctionCallFromConstructorTest.o: NotAbstractFunctionCallFromConstructorTest.cpp NotAbstractFunctionCallFromConstructorTest.h
	g++ -c -Wall NotAbstractFunctionCallFromConstructorTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

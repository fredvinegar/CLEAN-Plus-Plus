prog: ComplexConditionalTest1.o ComplexConditionalTest2.o ComplexConditionalTest3.o NotComplexConditionalTest.o
	echo ""

ComplexConditionalTest1.o: ComplexConditionalTest1.cpp ComplexConditionalTest1.h
	g++ -c -Wall ComplexConditionalTest1.cpp -nostartfiles -I.

ComplexConditionalTest2.o: ComplexConditionalTest2.cpp ComplexConditionalTest2.h
	g++ -c -Wall ComplexConditionalTest2.cpp -nostartfiles -I.

ComplexConditionalTest3.o: ComplexConditionalTest3.cpp ComplexConditionalTest3.h
	g++ -c -Wall ComplexConditionalTest3.cpp -nostartfiles -I.

NotComplexConditionalTest.o: NotComplexConditionalTest.cpp NotComplexConditionalTest.h
	g++ -c -Wall NotComplexConditionalTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

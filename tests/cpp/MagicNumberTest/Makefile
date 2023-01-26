prog: MagicNumberTest1.o MagicNumberTest2.o MagicNumberTest3.o MagicNumberTest4.o MagicNumberTest5.o NotMagicNumberTest.o
	echo ""

MagicNumberTest1.o: MagicNumberTest1.cpp MagicNumberTest1.h
	g++ -c -Wall MagicNumberTest1.cpp -nostartfiles -I.

MagicNumberTest2.o: MagicNumberTest2.cpp MagicNumberTest2.h
	g++ -c -Wall MagicNumberTest2.cpp -nostartfiles -I.

MagicNumberTest3.o: MagicNumberTest3.cpp MagicNumberTest3.h
	g++ -c -Wall MagicNumberTest3.cpp -nostartfiles -I.

MagicNumberTest4.o: MagicNumberTest4.cpp MagicNumberTest4.cpp
	g++ -c -Wall MagicNumberTest4.cpp -nostartfiles -I.

MagicNumberTest5.o: MagicNumberTest5.cpp MagicNumberTest5.h
	g++ -c -Wall MagicNumberTest5.cpp -nostartfiles -I.

NotMagicNumberTest.o: NotMagicNumberTest.cpp NotMagicNumberTest.h
	g++ -c -Wall NotMagicNumberTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

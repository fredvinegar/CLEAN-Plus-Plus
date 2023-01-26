prog: EmptyCatchClauseTest.o NotEmptyCatchClauseTest.o
	echo ""

EmptyCatchClauseTest.o: EmptyCatchClauseTest.cpp EmptyCatchClauseTest.h
	g++ -c -Wall EmptyCatchClauseTest.cpp -nostartfiles -I.

NotEmptyCatchClauseTest.o: NotEmptyCatchClauseTest.cpp NotEmptyCatchClauseTest.h
	g++ -c -Wall NotEmptyCatchClauseTest.cpp -nostartfiles -I.

clean:
	rm -f *.o

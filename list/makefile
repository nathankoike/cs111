tester: tester.o list.o
	g++ -o tester tester.o list.o

tester.o: tester.cc list.h
	g++ -c tester.cc

list.o: list.cc list.h
	g++ -c list.cc

clean:
	rm -f *.o tester *~

auth:   auth.o tester.o
	g++ -o auth auth.o tester.o

auth.o: auth.cc list.h
	g++ -c auth.cc


teststack: teststack.o stack.o
	g++ -o teststack teststack.o stack.o

stack.o: stack.cc stack.h
	g++ -c stack.cc

teststack.o: teststack.cc stack.h
	g++ -c teststack.cc

clean:
	rm -f *.o teststack *~

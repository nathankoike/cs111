sequence: sequence.o testseq.o
	g++ -o sequence sequence.o testseq.o
sequence.o: sequence.cc sequence.h
	g++ -c sequence.o sequence.cc
testseq.o: testseq.cc sequence.h
	g++ -c testseq.o testseq.cc

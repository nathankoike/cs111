studentcompile: wordfind

wordfind: wordfind.o
	g++ -o wordfind wordfind.o -lwg

wordfind.o: wordfind.cc
	g++ -c wordfind.cc


# Campbell only below:

SKELDIR=/home/acampbel/111/skel/wordfind

wordgrid.o: wordgrid.cc wordgrid.h
	g++ -c wordgrid.cc

install: wordgrid.o wordgrid.h
	g++ -fpic -c wordgrid.cc
	g++ -shared -o libwg.so wordgrid.o
	mv libwg.so ~/111/lib
	cp wordgrid.h ~/111/include
	chmod a+r ~/111/lib/libwg.so
	chmod a+r ~/111/include/wordgrid.h
	rm -rf $(SKELDIR)
	mkdir -p $(SKELDIR)
	chmod a+rx $(SKELDIR)
	cp wordfindskel.cc $(SKELDIR)/wordfind.cc
	cp makefile $(SKELDIR)/makefile
	cp sample.in $(SKELDIR)/sample.in
	chmod a+r $(SKELDIR)/*


all: compress uncompress

uncompress: compress
	ln -s compress uncompress

compress: compress.cc pq.cc
	g++ -o compress compress.cc

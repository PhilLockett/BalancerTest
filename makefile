# Makefile for Balancer unit tests.
objects  = test.o
objects += unittest.o

headers  = unittest.h
headers += TextFile.h

options = -std=c++20

test:	$(objects)	$(headers)
	g++ $(options) -o test $(objects)

%.o:	%.cpp	$(headers)
	g++ $(options) -c -o $@ $<

format:
	tfc -s -u -r test.cpp
	tfc -s -u -r unittest.cpp
	tfc -s -u -r unittest.h
	tfc -s -u -r BinaryFile.h
	tfc -s -u -r TextFile.h

clean:
	rm -f *.exe *.o

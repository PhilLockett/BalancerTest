# Makefile for Balancer unit tests.
objects  = test.o
objects += unittest.o
objects += Utilities.o
objects += Side.o

headers  = unittest.h
headers += Utilities.h
headers += Side.h
headers += TextFile.h

options = -std=c++20

test:	$(objects)	$(headers)
	g++ $(options) -o test $(objects)
	./test

%.o:	%.cpp	$(headers)
	g++ $(options) -c -o $@ $<

format:
	tfc -s -u -r test.cpp
	tfc -s -u -r unittest.cpp
	tfc -s -u -r unittest.h
	tfc -s -u -r Utilities.cpp
	tfc -s -u -r Utilities.h
	tfc -s -u -r Side.cpp
	tfc -s -u -r Side.h
	tfc -s -u -r TextFile.h

clean:
	rm -f *.exe *.o

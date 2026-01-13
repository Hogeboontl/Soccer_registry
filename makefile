soc: soclib.o soc.o
		g++ -std=c++11 soclib.o soc.o -o soc
soc.o: soc.cpp soc.h
		g++ -std=c++11 -c soc.cpp
soclib.o: soclib.cpp
		g++ -std=c++11 -c soclib.cpp
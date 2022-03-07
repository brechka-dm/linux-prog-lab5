all: prog1 prog2
prog1: prog1.cpp
	g++ prog1.cpp -o prog1 -pthread -std=c++11
prog2: prog2.cpp
	g++ prog2.cpp -o prog2 -pthread -std=c++11

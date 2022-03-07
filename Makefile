all: prog1
prog1: prog1.cpp
	g++ prog1.cpp -o prog1 -pthread -std=c++11

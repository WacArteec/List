all: hello

hello: main.o list.o
	g++ main.o list.o -o hello1

main.o: main.cpp
	g++ -c main.cpp

list.o: list.cpp
	g++ -c list.cpp
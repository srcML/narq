CPPFLAGS=-Wall -I /src

all: narq

narq: main.o tools.o
	g++ -o narq main.o tools.o

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp -o main.o

tools.o: tools.cpp
	g++ $(CPPFLAGS) -c tools.cpp -o tools.o

clean: 
	rm -r main.o tools.o narq

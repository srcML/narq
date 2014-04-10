BIN=bin
SRC=src
TEST=test/src
CPPFLAGS=-Wall -I /src

all: narq test

$(BIN)/test.o: 
	g++ $(CPPFLAGS) -c $(TEST)/test.cpp -o $(BIN)/test.o

narq: $(BIN)/main.o $(BIN)/tools.o
	g++ -o $(BIN)/narq $(BIN)/main.o $(BIN)/tools.o

$(BIN)/main.o: $(SRC)/main.cpp
	g++ $(CPPFLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o

$(BIN)/tools.o: $(SRC)/tools.cpp
	g++ $(CPPFLAGS) -c $(SRC)/tools.cpp -o $(BIN)/tools.o

test: $(BIN)/test.o $(BIN)/tools.o
	g++ -o $(BIN)/test $(BIN)/test.o $(BIN)/tools.o

clean: 
	rm -r $(BIN)/*

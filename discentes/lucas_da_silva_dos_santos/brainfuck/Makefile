# Build bcc brainfuck interpreter

.PHONY: release debug run clean

STD=-std=c11
FLAGS= -W -Wall -pedantic
SRC=src
LIB=$(SRC)/libraries
BIN=bin

run: release $(BIN)/example.bf
	./$(BIN)/brainfuck example.bf

release: $(BIN)/brainfuck

debug: FLAGS += -g -O0
debug: $(BIN)/brainfuck $(BIN)/example.bf

$(BIN)/brainfuck: $(BIN)/main.o $(BIN)/stack.o $(BIN)/list.o $(BIN)/node.o $(BIN)/data.o
	gcc $(STD) -o $(BIN)/brainfuck $(BIN)/main.o $(BIN)/stack.o $(BIN)/list.o $(BIN)/node.o $(BIN)/data.o $(FLAGS)

$(BIN)/main.o: $(SRC)/main.c $(BIN)
	gcc $(STD) -o $(BIN)/main.o $(SRC)/main.c -c $(FLAGS)

$(BIN)/stack.o: $(LIB)/stack/stack.c $(BIN)
	gcc $(STD) -o $(BIN)/stack.o $(LIB)/stack/stack.c -c $(FLAGS)

$(BIN)/list.o: $(LIB)/list/list.c $(BIN)
	gcc $(STD) -o $(BIN)/list.o $(LIB)/list/list.c -c $(FLAGS)

$(BIN)/node.o: $(LIB)/node/node.c $(BIN)
	gcc $(STD) -o $(BIN)/node.o $(LIB)/node/node.c -c $(FLAGS)

$(BIN)/data.o: $(LIB)/data.c $(BIN)
	gcc $(STD) -o $(BIN)/data.o $(LIB)/data.c -c $(FLAGS)

$(BIN)/example.bf: $(BIN)
	cp example.bf $(BIN)/example.bf

$(BIN):
	mkdir $(BIN)

clean:
	rm -rf $(BIN)
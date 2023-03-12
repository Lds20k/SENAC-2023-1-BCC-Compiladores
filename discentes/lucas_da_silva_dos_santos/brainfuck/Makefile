# Build bcc brainfuck interpreter

.PHONY: release debug run clean

STD=-std=c11
FLAGS= -W -Wall -pedantic

run: release bin/example.bf
	./bin/brainfuck example.bf

release: bin/brainfuck

debug: FLAGS += -g -O0
debug: bin/brainfuck

bin/brainfuck: bin/main.o
	gcc $(STD) -o bin/brainfuck bin/main.o $(FLAGS)

bin/main.o: main.c bin
	gcc $(STD) -o bin/main.o main.c -c $(FLAGS)

bin/example.bf: bin
	cp example.bf bin/example.bf

bin:
	mkdir bin

clean:
	rm -rf bin
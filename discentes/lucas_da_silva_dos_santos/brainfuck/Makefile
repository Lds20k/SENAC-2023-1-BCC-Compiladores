# Build bcc brainfuck interpreter

.PHONY: release debug run clean

STD=-std=c11
FLAGS=-g -W -Wall -lm -pedantic

run: bin/brainfuck
	./bin/brainfuck

release: bin/brainfuck

debug: FLAGS += -g -O0
debug: bin/brainfuck

bin/brainfuck: bin/main.o
	gcc $(STD) -o bin/brainfuck bin/main.o $(FLAGS)

bin/main.o: main.c bin
	gcc $(STD) -o bin/main.o main.c -c $(FLAGS)

bin:
	mkdir bin

clean:
	rm -rf bin
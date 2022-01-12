all: build

build: dir main
	gcc ./obj/main.o -o ./bin/poker

main:
	gcc -c ./src/main.c -o ./obj/main.o

dir:
	mkdir -p obj bin

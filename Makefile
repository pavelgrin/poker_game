all: build

build: dir main card_deck dealing combination view
	gcc ./obj/main.o ./obj/card_deck.o ./obj/dealing.o ./obj/combination.o ./obj/view.o -o ./bin/poker

main:
	gcc -c ./src/main.c -o ./obj/main.o

card_deck:
	gcc -c ./src/card_deck.c -o ./obj/card_deck.o

dealing:
	gcc -c ./src/dealing.c -o ./obj/dealing.o

combination:
	gcc -c ./src/combination.c -o ./obj/combination.o

view:
	gcc -c ./src/view.c -o ./obj/view.o

dir:
	mkdir -p obj bin

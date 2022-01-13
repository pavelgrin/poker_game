#include "./dealing.h"

void shuffle(int deck[][13]) {
    int rand_row;
    int rand_column;
    int temp_var;

    srand(time(NULL));

    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 13; column++) {
            rand_row = rand() % 4;
            rand_column = rand() % 13;
            
            temp_var = deck[rand_row][rand_column];

            deck[rand_row][rand_column] = deck[row][column];
            deck[row][column] = temp_var;
        }
    }
}

void deal(int cards[][2], const int length, const int deck[][13]) {
    static int card = 0;
    int l = card + length;

    int row;
    int column;
    int number_of_card = 0;

    int is_found = 0;

    for (; card < l; card++) {
        for (row = 0; row < 4; row++) {
            for (column = 0; column < 13; column++) {
                if (deck[row][column] == card) {
                    cards[number_of_card][0] = column;
                    cards[number_of_card][1] = row;

                    number_of_card += 1;

                    is_found = 1;
                    break;
                }
            }

            if (is_found) {
                is_found = 0;
                break;
            }
        }
    }
}

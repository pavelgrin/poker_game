#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int deck[][13]);
void deal(int player[][2], const int length, const int deck[][13]);

int checkCombination(const int player_cards[][2], const char *face[]);

void printCards(
    const int cards[][2], const int length, const int is_face_down,
    const char *suit[], const char *face[]
);

int main(void) {
    const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    const char *face[13] = {
        "Ace", "Deuce", "Three", "Four",
        "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King",
    };

    int deck[4][13] = {
        {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 },
        { 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 },
        { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
    };

    int dealer[5][2] = { 0 };
    int player[5][2] = { 0 };

    srand(time(NULL));

    shuffle(deck);

    deal(dealer, 5, deck);
    deal(player, 5, deck);

    printf("Cards of dealer:\n");
    printf("=================\n");
    printCards(dealer, 5, 1, suit, face);

    printf("\nCards of player:\n");
    printf("=================\n");
    printCards(player, 5, 0, suit, face);

    printf("\nPlayer has ");
    checkCombination(player, face);

    printf("\nEnter the card numbers you would like to replace ");
    printf("(1-5 or -1 to complete)\n");

    int numbers_of_card[5] = {0};
    for (int i = 0; i < 5 && numbers_of_card[i - 1] != -1; i++) {
        scanf("%d", &numbers_of_card[i]);
        if (~numbers_of_card[i]) numbers_of_card[i] -= 1;
        deal(&player[numbers_of_card[i]], 1, deck);
    }

    printf("\nCards of dealer:\n");
    printf("=================\n");
    printCards(dealer, 5, 0, suit, face);

    printf("\nCards of player:\n");
    printf("=================\n");
    printCards(player, 5, 0, suit, face);

    printf("\nDealer has ");
    int power1 = checkCombination(dealer, face);
    printf("\nPlayer has ");
    int power2 = checkCombination(player, face);

    if (power1 > power2)
        printf("\nDealer won\n");
    else if (power1 < power2)
        printf("\nPlayer won\n");
    else
        printf("\nIt is draw\n");

    return 0;
}

void shuffle(int deck[][13]) {
    int rand_row;
    int rand_column;
    int temp_var;

    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 13; column++) {
            rand_row = rand() % 4;
            rand_column = rand() % 13;
            
            temp_var = deck[rand_row][rand_column];
            printf("%d ", temp_var);
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

void printCards(
    const int cards[][2], const int length, const int is_face_down,
    const char *suit[], const char *face[]
) {
    for (int i = 0; i < length; i++) {
        if (is_face_down)
            printf("%5s of %-8s %d\n", "Back", "Card", i + 1);
        else
            printf("%5s of %-8s %d\n", face[cards[i][0]], suit[cards[i][1]], i + 1);
    }
}

int checkCombination(const int player_cards[][2], const char *face[]) {
    int getScoreOfCards(const int player_cards[][2]);
    int getHighCard(const int player_cards[][2]);
    int checkOnePair(const int player_cards[][2]);
    int checkTwoPairs(const int player_cards[][2]);
    int checkThreeOfKind(const int player_cards[][2]);
    int checkStraight(const int player_cards[][2]);
    int checkFlush(const int player_cards[][2]);
    int checkFullHouse(const int player_cards[][2]);
    int checkFourOfKind(const int player_cards[][2]);

    const int max_score_of_straight = 1741522; // it's max score of TJQKA offsuit

    const int score_of_cards = getScoreOfCards(player_cards);
    const int high_card = getHighCard(player_cards);

    const int four_of_kind = checkFourOfKind(player_cards);
    const int full_house = checkFullHouse(player_cards);
    const int flush = checkFlush(player_cards);
    const int straight = checkStraight(player_cards);
    const int three_of_kind = checkThreeOfKind(player_cards);
    const int two_pairs = checkTwoPairs(player_cards);
    const int one_pair = checkOnePair(player_cards);


    if (flush && straight == max_score_of_straight) {
        printf("Royal flush\n");
        return flush + straight + score_of_cards;
    }
    
    if (flush && straight) {
        printf("Straight flush\n");
        return flush + straight + score_of_cards;
    }

    if (four_of_kind) {
        printf("Four of a kind\n");
        return four_of_kind + score_of_cards;
    }

    if (full_house) {
        printf("Full house\n");
        return full_house + score_of_cards;
    }

    if (flush) {
        printf("Flush\n");
        return flush + score_of_cards;
    }

    if (straight) {
        printf("Straight\n");
        return straight + score_of_cards;
    }

    if (three_of_kind) {
        printf("Three of a kind\n");
        return three_of_kind + score_of_cards;
    }

    if (two_pairs) {
        printf("Two pairs\n");
        return two_pairs + score_of_cards;
    }

    if (one_pair) {
        printf("One pair\n");
        return one_pair + score_of_cards;
    }

    printf("%s-high\n", face[high_card]);
    return score_of_cards;
}

int getScoreOfCards(const int player_cards[][2]) {
    /*
        6  = 16-16 (min-max value)
        7  = 17-24
        8  = 25-36
        9  = 37-59
        10 = 60-104
        11 = 105-193
        12 = 194-363
        13 = 364-697

        from 2 to ace
        1 2 3 4 5 6 7  8  9 10 11  12  13
        1 2 3 4 5 6 7 15 27 50 95 184 353
    */

    const int face_score[] = {
        353, 1, 2, 3, 4, 5, 6, 7, 15, 27, 50, 95, 184,
    };

    int score = 0;

    for (int i = 0; i < 5; i++) {
        score += face_score[player_cards[i][0]];
    }

    return score;
}

int getHighCard(const int player_cards[][2]) {
    int max = -1;

    for (int i = 0; i < 5; i++) {
        if (player_cards[i][0] == 0) return player_cards[i][0];
        if (player_cards[i][0] > max) max = player_cards[i][0];
    }

    return max;
}

int checkOnePair(const int player_cards[][2]) {
    const int score = 700; // > than max score of nothing
    int i, j;
    int count = 1;

    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 5; j++) {
            if (player_cards[i][0] == player_cards[j][0])
                count += 1;
        }

        if (count != 2)
            count = 1;
        // if ace, 0 replace by 13
        else
            return score * (player_cards[i][0] ? player_cards[i][0] : 13);
    }

    return 0;
}

int checkTwoPairs(const int player_cards[][2]) {
    const int score = 10200; // > than max score of one pair
    int face_of_two = -1;
    int face_of_two2 = -1;

    for (int i = 0; i < 5; i++) {
        if (player_cards[i][0] == face_of_two || player_cards[i][0] == face_of_two2) {
            continue;
        }

        int count = 0;

        for (int j = 0; j < 5; j++) {
            if (player_cards[i][0] == player_cards[j][0])
                count += 1;
        }

        if (count == 2) {
            if (~face_of_two)
                face_of_two2 = player_cards[i][0];
            else
                face_of_two = player_cards[i][0];
        }
    }

    if (~face_of_two && ~face_of_two2) {
        // if ace, 0 replace by 13
        face_of_two = face_of_two ? face_of_two : 13;
        face_of_two2 = face_of_two2 ? face_of_two2 : 13;

        if (face_of_two > face_of_two2)
            return score * face_of_two + face_of_two2;

        return score * face_of_two2 + face_of_two;
    }

    return 0;
}

int checkThreeOfKind(const int player_cards[][2]) {
    const int score = 133800; // > than max score of two pairs
    int count = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (player_cards[i][0] == player_cards[j][0])
                count += 1;
        }

        if (count != 3)
            count = 1;
        // if ace, 0 replace by 13
        else
            return score * (player_cards[i][0] ? player_cards[i][0] : 13);
    }

    return 0;
}

int checkStraight(const int player_cards[][2]) {
    const int score = 1740800; // > than max score of three of kind
    int i;
    int min = player_cards[0][0];
    int max = player_cards[0][0];
    int count = 1;

    for (i = 1; i < 5; i++) {
        if (player_cards[i][0] < min)
            min = player_cards[i][0];
        if (player_cards[i][0] > max)
            max = player_cards[i][0];
    }

    if (!min) max = 13; // if max == ace, 0 replace by 13

    for (i = 0; i < 5;) {
        // check TJQKA straight
        if ((min + 1) == player_cards[i][0] || (min == 0 && player_cards[i][0] == 9)) {
            min = player_cards[i][0];
            count += 1;
            i = 0;
        } else
            i += 1;
    }

    if (count != 5)
        return 0;

    return score + max;
}

int checkFlush(const int player_cards[][2]) {
    const int score = 1741600; // > than max score of straight
    int count = 0;

    for (int i = 0; i < 5; i++) {
        if (player_cards[0][1] == player_cards[i][1])
            count += 1;
        else
            break;
    }

    if (count == 5)
        return score;

    return 0;
}

int checkFullHouse(const int player_cards[][2]) {
    const int score = 1742300; // > than max score of flush
    int face_of_three = -1;
    int face_of_two = -1;

    for (int i = 0; i < 5; i++) {
        if (player_cards[i][0] == face_of_three || player_cards[i][0] == face_of_two) {
            continue;
        }

        int count = 0;

        for (int j = 0; j < 5; j++) {
            if (player_cards[i][0] == player_cards[j][0])
                count += 1;
        }

        if (count == 3)
            face_of_three = player_cards[i][0];
        else if (count == 2)
            face_of_two = player_cards[i][0];
    }

    if (~face_of_three && ~face_of_two) {
        // if ace, 0 replace by 13
        face_of_three = face_of_three ? face_of_three : 13;
        face_of_two = face_of_two ? face_of_two : 13;

        return score * face_of_three + face_of_two;
    }

    return 0;
}

int checkFourOfKind(const int player_cards[][2]) {
    const int score = 22651400; // > than max score of full house
    int count = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (player_cards[i][0] == player_cards[j][0])
                count += 1;
        }

        if (count != 4)
            count = 1;
        // if ace, 0 replace by 13
        else
            return score * (player_cards[i][0] ? player_cards[i][0] : 13);
    }

    return 0;
}

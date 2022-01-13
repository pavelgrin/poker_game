
#include "./card_deck.h"
#include "./combination.h"

// it's max score of TJQKA
const int MAX_SCORE_OF_STRAIGHT = 1741522;

int getHighCard(const int player_cards[][2]) {
    int max = -1;

    for (int i = 0; i < 5; i++) {
        if (player_cards[i][0] == 0) return player_cards[i][0];
        if (player_cards[i][0] > max) max = player_cards[i][0];
    }

    return max;
}

int getCombination(const int player_cards[][2]) {
    const int four_of_kind = checkFourOfKind(player_cards);
    const int full_house = checkFullHouse(player_cards);
    const int flush = checkFlush(player_cards);
    const int straight = checkStraight(player_cards);
    const int three_of_kind = checkThreeOfKind(player_cards);
    const int two_pairs = checkTwoPairs(player_cards);
    const int one_pair = checkOnePair(player_cards);

    int comb_id = 0;

    if (flush && straight == MAX_SCORE_OF_STRAIGHT) {
        comb_id = 9;
    } else if (flush && straight) {
        comb_id = 8;
    } else if (four_of_kind) {
        comb_id = 7;
    } else if (full_house) {
        comb_id = 6;
    } else if (flush) {
        comb_id = 5;
    } else if (straight) {
        comb_id = 4;
    } else if (three_of_kind) {
        comb_id = 3;
    } else if (two_pairs) {
        comb_id = 2;
    } else if (one_pair) {
        comb_id = 1;
    }

    return comb_id;
}

int getCardsScore(const int player_cards[][2]) {
    // card value
    // 2 3 4 5 6 7 8  9 10  J  Q   K   A
    // 1 2 3 4 5 6 7 15 27 50 95 184 353

    const int face_score[] = {
        353, 1, 2, 3, 4, 5, 6, 7, 15, 27, 50, 95, 184,
    };

    int score = 0;

    for (int i = 0; i < 5; i++) {
        score += face_score[player_cards[i][0]];
    }

    return score + getCombScore(player_cards);
}


int getCombScore(const int player_cards[][2]) {
    const int four_of_kind = checkFourOfKind(player_cards);
    const int full_house = checkFullHouse(player_cards);
    const int flush = checkFlush(player_cards);
    const int straight = checkStraight(player_cards);
    const int three_of_kind = checkThreeOfKind(player_cards);
    const int two_pairs = checkTwoPairs(player_cards);
    const int one_pair = checkOnePair(player_cards);

    int comb_score = 0;

    if (flush && straight == MAX_SCORE_OF_STRAIGHT) {
        comb_score = flush + straight;
    } else if (flush && straight) {
        comb_score = flush + straight;
    } else if (four_of_kind) {
        comb_score = four_of_kind;
    } else if (full_house) {
        comb_score = full_house;
    } else if (flush) {
        comb_score = flush;
    } else if (straight) {
        comb_score = straight;
    } else if (three_of_kind) {
        comb_score = three_of_kind;
    } else if (two_pairs) {
        comb_score = two_pairs;
    } else if (one_pair) {
        comb_score = one_pair;
    }

    return comb_score;
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

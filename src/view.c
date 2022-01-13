#include "./view.h"
#include "./card_deck.h"

void printCards(const int cards[][2], const int length, const int is_face_down) {
    for (int i = 0; i < length; ++i) {
        if (is_face_down)
            printf("%5s of %-8s %d\n", "Back", "Card", i + 1);
        else
            printf("%5s of %-8s %d\n", card_face[cards[i][0]], card_suit[cards[i][1]], i + 1);
    }
}

void displayDealerCards(const int cards[][2], const int is_face_down) {
    printf("\nCards of dealer:\n");
    printf("=================\n");
    printCards(cards, 5, is_face_down);
}

void displayPlayerCards(const int cards[][2], const int is_face_down) {
    printf("\nCards of player:\n");
    printf("=================\n");
    printCards(cards, 5, is_face_down);
}

void displayDealerCombination(int comb_id, int high_card) {
    if (comb_id) {
        printf("\nDealer has %s\n", card_combination[comb_id]);
    } else {
        printf("\nDealer has %s-high\n", card_face[high_card]);
    }
}

void displayPlayerCombination(int comb_id, int high_card) {
    if (comb_id) {
        printf("\nPlayer has %s\n", card_combination[comb_id]);
    } else {
        printf("\nPlayer has %s-high\n", card_face[high_card]);
    }
}

void displayResult(int player_score, int dealer_score) {
    if (dealer_score > player_score)
        printf("\nDealer won\n");
    else if (dealer_score < player_score)
        printf("\nPlayer won\n");
    else
        printf("\nIt is draw\n");;
}

void promptToReplaceCards(void) {
    printf("\nEnter the card numbers you would like to replace ");
    printf("(1-5 or -1 to complete)\n");
}

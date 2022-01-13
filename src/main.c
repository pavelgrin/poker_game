#include <stdio.h>

#include "./card_deck.h"
#include "./dealing.h"
#include "./combination.h"
#include "./view.h"

int main(void) {
    int dealer[5][2] = { 0 };
    int player[5][2] = { 0 };

    int dealer_comb_id = 0;
    int dealer_high_card = 0;
    int player_comb_id = 0;
    int player_high_card = 0;

    shuffle(card_deck);

    deal(dealer, 5, card_deck);
    deal(player, 5, card_deck);

    displayDealerCards(dealer, 1);
    displayPlayerCards(player, 0);

    player_high_card = getHighCard(player);
    player_comb_id = getCombination(player);
    displayPlayerCombination(player_comb_id, player_high_card);

    promptToReplaceCards();

    int numbers_of_card[5] = {0};
    for (int i = 0; i < 5 && numbers_of_card[i - 1] != -1; i++) {
        scanf("%d", &numbers_of_card[i]);
        if (~numbers_of_card[i]) numbers_of_card[i] -= 1;
        deal(&player[numbers_of_card[i]], 1, card_deck);
    }

    displayDealerCards(dealer, 0);
    displayPlayerCards(player, 0);

    dealer_high_card = getHighCard(dealer);
    dealer_comb_id = getCombination(dealer);
    displayDealerCombination(dealer_comb_id, dealer_high_card);

    player_high_card = getHighCard(player);
    player_comb_id = getCombination(player);
    displayPlayerCombination(player_comb_id, player_high_card);

    int player_score = getCardsScore(player);
    int dealer_score = getCardsScore(dealer);
    displayResult(player_score, dealer_score);

    return 0;
}

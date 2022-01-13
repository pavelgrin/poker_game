#pragma once

int getHighCard(const int player_cards[][2]);
int getCombination(const int player_cards[][2]);
int getCardsScore(const int player_cards[][2]);

int getCombScore(const int player_cards[][2]);
int checkFourOfKind(const int player_cards[][2]);
int checkFullHouse(const int player_cards[][2]);
int checkFlush(const int player_cards[][2]);
int checkStraight(const int player_cards[][2]);
int checkThreeOfKind(const int player_cards[][2]);
int checkTwoPairs(const int player_cards[][2]);
int checkOnePair(const int player_cards[][2]);

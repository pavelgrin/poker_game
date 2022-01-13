#pragma once

#include <stdio.h>

void displayDealerCards(const int cards[][2], const int is_face_down);
void displayPlayerCards(const int cards[][2], const int is_face_down);

void displayDealerCombination(int comb_id, int high_card);
void displayPlayerCombination(int comb_id, int high_card);

void displayResult(int dealer_power, int player_power);

void promptToReplaceCards(void);

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;

void shuffle(int deck[][13]);
void deal(
  int player[][2], const int deck[][13], const char *face[], const char *suit[]
);
void checkCombination(const int player_cards[][2], const char *face[]);

int main(void) {
  const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

  const char *face[13] = {
    "Ace", "Deuce", "Three", "Four",
    "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King",
  };

  int deck[4][13] = { 0 };
  int player_cards[5][2] = { 0 };

  srand(time(NULL));

  shuffle(deck);
  deal(player_cards, deck, face, suit);
  checkCombination(player_cards, face);

  return 0;
}

void shuffle(int deck[][13]) {
  int row;
  int column;
  int card;

  for (card = 1; card <=52; card++) {
    do {
      row = rand() % 4;
      column = rand() % 13;
    } while (deck[row][column] != 0);

    deck[row][column] = card;
  }
}

void deal(
  int player[][2], const int deck[][13], const char *face[], const char *suit[]
) {
  int row;
  int column;
  int card;

  for (card = 1; card <= 5; card++) {
    for (row = 0; row < 4; row++) {
      for (column = 0; column < 13; column++) {
        if (deck[row][column] == card) {
          player[card][0] = column;
          player[card][1] = row;

          printf("%5s of %-8s\n", face[column], suit[row]);
        }
      }
    }
  }
}

void checkCombination(const int player_cards[][2], const char *face[]) {
  bool checkFourOfKind(const int player_cards[][2]);
  bool checkFullHouse(const int player_cards[][2]);
  bool checkFlush(const int player_cards[][2]);
  bool checkStraight(const int player_cards[][2]);
  bool checkThreeOfKind(const int player_cards[][2]);
  bool checkTwoPairs(const int player_cards[][2]);
  bool checkOnePair(const int player_cards[][2]);
  int checkHighCard(const int player_cards[][2]);

  bool is_four_of_kind = checkFourOfKind(player_cards);
  bool is_full_house = checkFullHouse(player_cards);
  bool is_flush = checkFlush(player_cards);
  bool is_straight = checkStraight(player_cards);
  bool is_three_of_kind = checkThreeOfKind(player_cards);
  bool is_two_pairs = checkTwoPairs(player_cards);
  bool is_one_pair = checkOnePair(player_cards);
  int high_card = checkHighCard(player_cards);

  if (is_flush && is_straight && high_card == 0) printf("\nYou have royal flush\n");
  else if (is_flush && is_straight) printf("\nYou have straight flush\n");
  else if (is_four_of_kind) printf("\nYou have four of a kind\n");
  else if (is_full_house) printf("\nYou have full house\n");
  else if (is_flush) printf("\nYou have a flush\n");
  else if (is_straight) printf("\nYou have straight\n");
  else if (is_three_of_kind) printf("\nYou have three of a kind\n");
  else if (is_two_pairs) printf("\nYou have two pairs\n");
  else if (is_one_pair) printf("\nYou have one pair\n");
  else printf("\nYou have %s-high\n", face[high_card]);
}

bool checkFourOfKind(const int player_cards[][2]) {}
bool checkFullHouse(const int player_cards[][2]) {}
bool checkFlush(const int player_cards[][2]) {}
bool checkStraight(const int player_cards[][2]) {}
bool checkThreeOfKind(const int player_cards[][2]) {}
bool checkTwoPairs(const int player_cards[][2]) {}
bool checkOnePair(const int player_cards[][2]) {}
int checkHighCard(const int player_cards[][2]) {}

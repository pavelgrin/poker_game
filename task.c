#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;

void shuffle(int deck[][13]);
void checkCombination(const int player_cards[][2], const char *face[]);

void deal(
  int player[][2],
  const int deck[][13],
  const char *face[],
  const char *suit[]
);

int main(void) {
  const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

  const char *face[13] = {
    "Ace", "Deuce", "Three", "Four",
    "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King",
  };

  int deck[4][13] = { 0 };
  int player1[5][2] = { 0 };
  int player2[5][2] = { 0 };

  srand(time(NULL));

  shuffle(deck);

  deal(player1, deck, face, suit);
  deal(player2, deck, face, suit);

  checkCombination(player1, face);
  checkCombination(player2, face);

  return 0;
}

void shuffle(int deck[][13]) {
  int row;
  int column;

  for (int card = 0; card < 52; card++) {
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
  static int card = 0;
  int length = card + 5;

  int row;
  int column;
  int number_of_card = 0;

  for (; card < length; card++) {
    for (row = 0; row < 4; row++) {
      for (column = 0; column < 13; column++) {
        if (deck[row][column] == card) {
          player[number_of_card][0] = column;
          player[number_of_card][1] = row;

          number_of_card += 1;

          printf("%5s of %-8s\n", face[column], suit[row]);
        }
      }
    }
  }

  printf("\n");
}

void checkCombination(const int player_cards[][2], const char *face[]) {
  bool checkFourOfKind(const int player_cards[][2]);
  bool checkFullHouse(const int player_cards[][2]);
  bool checkFlush(const int player_cards[][2]);
  int checkStraight(const int player_cards[][2]);
  bool checkThreeOfKind(const int player_cards[][2]);
  bool checkTwoPairs(const int player_cards[][2]);
  bool checkOnePair(const int player_cards[][2]);
  int checkHighCard(const int player_cards[][2]);

  bool is_four_of_kind = checkFourOfKind(player_cards);
  bool is_full_house = checkFullHouse(player_cards);
  bool is_flush = checkFlush(player_cards);
  int is_straight = checkStraight(player_cards);
  bool is_three_of_kind = checkThreeOfKind(player_cards);
  bool is_two_pairs = checkTwoPairs(player_cards);
  bool is_one_pair = checkOnePair(player_cards);
  int high_card = checkHighCard(player_cards);

  if (is_flush && is_straight == 2 && high_card == 0) {
    printf("\nYou have royal flush\n");
  } else if (is_flush && is_straight) printf("\nYou have straight flush\n");
  else if (is_four_of_kind) printf("\nYou have four of a kind\n");
  else if (is_full_house) printf("\nYou have full house\n");
  else if (is_flush) printf("\nYou have a flush\n");
  else if (is_straight) printf("\nYou have straight\n");
  else if (is_three_of_kind) printf("\nYou have three of a kind\n");
  else if (is_two_pairs) printf("\nYou have two pairs\n");
  else if (is_one_pair) printf("\nYou have one pair\n");
  else printf("\nYou have %s-high\n", face[high_card]);
}

bool checkFourOfKind(const int player_cards[][2]) {
  int i, j;
  int count = 1;

  for (i = 0; i < 2; i++) {
    for (j = i + 1; j < 5; j++) {
      if (player_cards[i][0] == player_cards[j][0]) count += 1;
    }

    if (count != 4) count = 1;
    else return true;
  }

  return false;
}

bool checkFullHouse(const int player_cards[][2]) {
  int face_of_three = -1;
  int face_of_two = -1;

  for (int i = 0; i < 5; i++) {
    if (player_cards[i][0] == face_of_three || player_cards[i][0] == face_of_two) {
      continue;
    }

    int count = 0;

    for (int j = 0; j < 5; j++) {
      if (player_cards[i][0] == player_cards[j][0]) count += 1;
    }

    if (count == 3) face_of_three = player_cards[i][0];
    else if (count == 2) face_of_two = player_cards[i][0];
  }

  if (~face_of_three && ~face_of_two) return true;
  return false;
}

bool checkFlush(const int player_cards[][2]) {
  int count = 0;

  for (int i = 0; i < 5; i++) {
    if (player_cards[0][1] == player_cards[i][1]) count += 1;
    else break;
  }

  if (count == 5) return true;
  return false;
}

int checkStraight(const int player_cards[][2]) {
  int i;
  int min = player_cards[0][0];
  int max = player_cards[0][0];
  int count = 1;

  for (i = 1; i < 5; i++) {
    if (player_cards[i][0] < min) min = player_cards[i][0];
    if (player_cards[i][0] > max) max = player_cards[i][0];
  }

  for (i = 0; i < 5;) {
    if ((min + 1) == player_cards[i][0] || (min == 0 && player_cards[i][0] == 9)) {
      min = player_cards[i][0];
      count += 1;
      i = 0;
    } else i += 1;
  }

  if (count != 5) return false;
  else if (max == 12) return 2;

  return true;
}

bool checkThreeOfKind(const int player_cards[][2]) {
  int count = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 5; j++) {
      if (player_cards[i][0] == player_cards[j][0]) count += 1;
    }

    if (count != 3) count = 1;
    else return true;
  }

  return false;
}

bool checkTwoPairs(const int player_cards[][2]) {
  int face_of_two = -1;
  int face_of_two2 = -1;

  for (int i = 0; i < 5; i++) {
    if (player_cards[i][0] == face_of_two || player_cards[i][0] == face_of_two2) {
      continue;
    }

    int count = 0;

    for (int j = 0; j < 5; j++) {
      if (player_cards[i][0] == player_cards[j][0]) count += 1;
    }

    if (count == 2) {
      if (~face_of_two) face_of_two2 = player_cards[i][0];
      else face_of_two = player_cards[i][0];
    }
  }

  if (~face_of_two && ~face_of_two2) return true;
  return false;
}

bool checkOnePair(const int player_cards[][2]) {
  int i, j;
  int count = 1;

  for (i = 0; i < 4; i++) {
    for (j = i + 1; j < 5; j++) {
      if (player_cards[i][0] == player_cards[j][0]) count += 1;
    }

    if (count != 2) count = 1;
    else return true;
  }

  return false;
}

int checkHighCard(const int player_cards[][2]) {
  int max = player_cards[0][0];

  for (int i = 0; i < 5; i++) {
    if (player_cards[i][0] == 0) return player_cards[i][0]; 
    if (player_cards[i][0] > max) max = player_cards[i][0];
  }

  return max;
}

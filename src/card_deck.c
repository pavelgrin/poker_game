const char *card_suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

const char *card_face[13] = {
    "Ace", "Deuce", "Three", "Four",
    "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King",
};

const char *card_combination[10] = {
    "High card",
    "One pair",
    "Two pairs",
    "Three of a kind",
    "Straight",
    "Flush",
    "Full house",
    "Four of a kind",
    "Straight flush",
    "Royal flush",
};

int card_deck[4][13] = {
    {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 },
    { 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 },
    { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
};

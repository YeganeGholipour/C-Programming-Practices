#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define DECK_SIZE 52

void deal_hand(int num_cards);

int main() {
    int num_cards;

    // Initialize random number generator
    srand(time(NULL));

    // Ask user for number of cards
    printf("Enter number of cards in hand: ");
    scanf("%d", &num_cards);

    // Ensure valid input
    if (num_cards < 1 || num_cards > DECK_SIZE) {
        printf("Invalid number of cards. Choose between 1 and 52.\n");
        return 1;
    }

    // Deal the hand
    deal_hand(num_cards);

    return 0;
}

void deal_hand(int num_cards) {
    // Arrays for ranks and suits
    char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char *suits[] = {"c", "d", "h", "s"};  // Clubs, Diamonds, Hearts, Spades

    int deck[NUM_RANKS][NUM_SUITS] = {0};  // Track used cards

    printf("Your hand: ");
    for (int i = 0; i < num_cards; i++) {
        int rank, suit;

        // Generate a unique card
        do {
            rank = rand() % NUM_RANKS;
            suit = rand() % NUM_SUITS;
        } while (deck[rank][suit]);  // Repeat if card is already chosen

        deck[rank][suit] = 1;  // Mark card as used
        printf("%s%s ", ranks[rank], suits[suit]);  // Print shorthand notation
    }
    printf("\n");
}

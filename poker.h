/*=============================================================================
|	Source code:   poker.h
|	Author:   Sean Quinn
|	Student ID: 1203714
|	Assignment:   Program #4 "Poker" 
|
|	Course: COP 4338 - Advanced Programming
|	Section: U04
|	Instructor: William Feild
|	Due Date:   Mar 9, 2017
|
|============================================================================*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

enum suits {CLUBS = 1, DIAMONDS, HEARTS, SPADES};
enum ranks {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		TEN, JACK, QUEEN, KING};

#define DECK_SIZE	53	/* number of cards in deck */
#define NUM_RANKS	13	/* number of ranks in a suit */
#define MAX_SUITNAME	9	/* longest suit name, "diamonds" + EOS */
#define MAX_RANKNAME	6	/* longest rank name + EOS */
#define CARD_INIT	1	/* initialize counting loops */
#define ZERO		0	
#define MAX_RANK	13	/* value of highest rank (king) */
#define MAX_SUIT	4	/* suits numbered 1-4 */
#define CPH		5	/* cards per hand fixed at 5 */
#define ARGS_EXP	3	/* expects 3 input arguments */
#define	MIN_PLYRS	1
#define MAX_PLYRS	7
#define TRUE		0
#define FALSE		1
#define HIGH_ACE	14

/* The folowing defines give the base rank scores used in calculating
 * 	winners. Listed in ascending order of value: */
#define PAIR_BASE	430168	
#define TWO_PAIR_BASE	30743				
#define THREE_KIND_BASE	2545	
#define STRAIGHT_BASE	2545		
#define FLUSH_BASE	10	
#define FULL_HOUSE_BASE	430168	
#define FOUR_KIND_BASE	183
#define STRAIGHT_FLUSH_BASE	183

/* Each card is represented by a structure consisting of:
 * i_d_num: an int 1-52. This is used to determine:
 * suit: Each 1-13 grouping of i_d_num selects one of the four suits.
 * 	Ascending numeric order is mapped to alphabetic order.
 * rank: Within each suit, the numbers 1-10 represent the numbered cards.
 * 	11 is Jack, 12 is Queen, and 13 is King.
 * suit_name: string representations of the names are included as
 * rank_name: part of the the struct
 */
typedef struct card {
	int i_d_num;
	int suit;
	int rank;
	char suit_name[MAX_SUITNAME];
	char rank_name[MAX_RANKNAME];
}Card;	

/* A hand is a structure containing a user-selected number of cards,
 * plus an integer number that identifies the hand within a game.
 * This being a stud poker simulation, the number of cards per hand
 * is fixed at 5 */
typedef struct Card {
	int hand_id;
	long score;
	Card hand[CPH + CARD_INIT];
}Hand;

/* A deck is just an array of type Card given a name for convenience */
typedef Card Deck[DECK_SIZE];

/*----------------------- Function Declarations -----------------------------*/

Card assign_card(int);
Card* create_deck(Deck);
Hand* dealHands(int, Deck, Hand[]);

Hand* deal_one_hand(int, int, int, Deck, Hand);

void display_all_hands(int, Hand[]);
void display_card(Card);
void display_deck(Deck);
void display_hand(Hand);
void get_nameofrank(int, char[]);
void get_nameofsuit(int, char[]);
void get_most(int, int*, int*);
int get_rank(int);
int get_largest(int*, int*, int*, int*, int*, int,
			int*, int*, int*, int*, int*);
long get_score(Hand);
int get_suit(int);
int get_winner(int, Hand[]);

/* The "has" functions are called when a hand of that type is identified.
 * They rearrange the cards in the hand from high to low value and 
 * process the hand */

int hasFlush(int);
int hasStraight(int[]);

/* The "is" functions calculate the score of each hand */
long isFlush(int, int, int, int, int);
long isFourKind(int, int);
long isFullHouse(int, int);
long isHighCard(int, int, int, int, int);
long isPair(int, int, int, int);
long isStraight(int);
long isStraightFlush(int);
long isThreeKind(int, int, int);
long isTwoPair(int, int, int);

Card* shuffle_deck(Deck);
int* sort_hand(int[], Card[], int*, int*, int*, int*, int*, int*);
int validate(int, int);
int validate_num_args(int);

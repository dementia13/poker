/*=============================================================================
|	Source code:   poker.c
|	Author:   Sean Quinn
|	Student ID: 1203714
|	Assignment:   Program #4 "Poker" 
|
|	Course: COP 4338 - Advanced Programming
|	Section: U04
|	Instructor: William Feild
|	Due Date:   Mar 9, 2017
|
|===========================================================================*/
#ifndef POKER
#define POKER "poker.h"
#endif
#include POKER

/*----------------- assign_card  ----------------------------------------------
 * function assign_card(int id) 
 *
 * Purpose: Receives an int that represents a card in a deck, assigns the
 * 	rank and suit both as an integer and as a string value 
 *
 * @param - int id - identifier, an int 1-52 that represents the card 
 *
 * @return Card - the complete structure representing a single card 
 *
-----------------------------------------------------------------------------*/
Card assign_card(int id){
	Card new_card;
	char suit_name[MAX_SUITNAME];
	char rank_name[MAX_RANKNAME];
	char *s_name = suit_name;
	char *r_name = rank_name;
	new_card.i_d_num = id;
		new_card.suit = get_suit(id);
		new_card.rank = get_rank(id);
		get_nameofsuit(new_card.suit, suit_name);
		get_nameofrank(new_card.rank, rank_name);
		strcpy(new_card.suit_name, s_name);
		strcpy(new_card.rank_name, r_name);	
	return new_card;
} 

/*----------------- create_deck ----------------------------------------------
 * function create_deck(Deck new_deck)
 *
 * Purpose: Generates a deck of cards. This is nothing special- it's just
 * 	a counting loop. Rank and suit to be assigned later by division.
 *
 * @param - Deck deck - array of type Card. Elements are populated as
 * 	the array is iterated through. 
 *
 * @return Card*- returned as pointer to first array element
 *
-----------------------------------------------------------------------------*/
Card* create_deck(Deck new_deck){
	Card *p_card;
	Card new_card;

	p_card = new_deck;
	p_card++;

	int id;
	char suit_name[MAX_SUITNAME];
	char rank_name[MAX_RANKNAME];
	char *s_name = suit_name;
	char *r_name = rank_name;
	for (id = CARD_INIT; id < DECK_SIZE; id++){
		p_card->i_d_num = id;
		p_card->suit = get_suit(id);
		p_card->rank = get_rank(id);
		get_nameofsuit(p_card->suit, suit_name);
		get_nameofrank(p_card->rank, rank_name);
		strcpy(p_card->suit_name, s_name);
		strcpy(p_card->rank_name, r_name);	
 		p_card++;
	} 
	return (p_card - DECK_SIZE);
}

/*----------------- dealHands ------------------------------------------------
 * function dealHands(int, Deck, Hand[]) 
 *
 * Purpose: Distributes cards from a generated deck to a user-specified
 * 	number of players. Each Hand is dealt in a separate function
 * 	and the array is assembled and returned here
 *
 * @param - int num_hands - a user-specified number of players
 * 	   Deck shuffled - the deck to be dealt
 * 	   Hand aHands[] - array of all hands in the game 
 *
 * @return Hand* - returns array of dealt Hands as pointer to first element
 *
-----------------------------------------------------------------------------*/
Hand* dealHands(int num_hands, Deck shuffled, 
		Hand aHands[]){
	int hand_count;
	int card_count;
	int game_count;
	int deck_count;

	Hand *p_Game;		
	p_Game = aHands;	
	Hand new_Hand;
	Hand *p_hand;
	p_hand = &new_Hand;
	Card *p_card;
	p_card++;
	p_hand++;
	p_Game++;

	/* These are to be passed to the function that deals the
 		individual hands. */ 
	int next_card;	/* Card that is dealt */ 
	int hand_offset; /* Tracks which hand is being dealt to */
	next_card = hand_offset = deck_count = CARD_INIT;

	for (game_count = CARD_INIT;
		game_count <= num_hands; 
			game_count++){

		p_hand = deal_one_hand(num_hands, next_card, hand_offset, 
			shuffled, new_Hand);

		*p_Game = *p_hand;
		p_Game++;

		/* reset deal counters */
		next_card++;
		hand_offset++;
		deck_count += CPH;	/* Tracks how many cards
			have been dealt from deck. It was already 
			validated that there will not be more hands
			dealt than cards in the deck, but this is
			an extra safeguard. */
	}
	if(deck_count >= DECK_SIZE){
		printf("%s\n", "Programming error: all cards dealt.");
	}
	return (p_Game - deck_count);
}

/*----------------- deal_one_hand --------------------------------------------
 * function deal_one_hand(int, int, int, Deck, Hand)
 *
 * Purpose: Deals a single Hand. Simulates a deal in round-robin fashion:
 * 	Deals a card from the deck, then skips (number of players -1) ahead
 * 	and deals the next. This simulates the way cards are dealt in an
 * 	actual game. 
 *
 * @param - int num_hands - user-selected number of players
 * 	    int next_card - the next card to be dealt from the deck. It is
 * 	    	incremented by the number of players each pass through the
 * 	    	calling function
 * 	    int hand_offset - tracks which hand is being dealt
 * 	   Deck shuffled - the Deck being dealt from
 * 	   Hand newHand - the Hand being populated  
 *
 * @return - dealt Hand as pointer to first array element 
-----------------------------------------------------------------------------*/
Hand* deal_one_hand(int num_hands, int next_card, 
		int hand_offset, Deck shuffled, Hand newHand){ 
	Hand *p_hand;
	int card_count;

	for(card_count = CARD_INIT; card_count <= CPH; card_count++){
		newHand.hand[card_count] = shuffled[next_card];
		next_card += num_hands;
		p_hand++;
	}		

	newHand.hand_id = hand_offset;
	p_hand = &newHand;
/*
	p_hand++;
*/
	newHand.score = get_score(newHand);
	p_hand = &newHand;

	return p_hand;
}

/*----------------- display_all_hands -----------------------------------------
 * function display_all_hands(int, Hand[])
 *
 * Purpose: Prints all hands in the game by calling function
 * 	to display single hand
 *
 * @param - int num_hands - user-selected number of players
 * 	   Hand allHands[] - array of all Hands in play 
 *
 * @return none. Is a print function.
-----------------------------------------------------------------------------*/
void display_all_hands(int num_hands, Hand allHands[num_hands]){
	int hand_count;
	for (hand_count = CARD_INIT; hand_count <= num_hands; hand_count++){
		printf("%s %d %s\n", "Displaying hand #", hand_count, ":");
		display_hand(allHands[hand_count]);
	}
	return;
}
			
/*----------------- display_card ----------------------------------------------
 * function display_card(Card d_card
 *
 * Purpose: Function for display of a e card from the deck. 
 * 	Prints name of rank and suit
 *
 * @param struct card d_card - a card, what else?
 *
 * @return none. Is a print function.
-----------------------------------------------------------------------------*/
void display_card(Card d_card){
	printf("%6s %s %s\n", d_card.rank_name, 
		" of ", d_card.suit_name);
	return;
}

/*----------------- display_deck ---------------------------------------------
 * function display_deck(Card show_deck)
 *
 * Purpose: Is passed a pointer to the deck of shuffled cards. Prints the 
 * 	contents of the current (shuffled and possibly dealt from) deck. 
 *
 * @param Card show_deck) - pointer to the first element of an array
 * 	representing the deck of cards
 *
 * @return none. Is a print function.
-----------------------------------------------------------------------------*/
void display_deck(Deck show_deck){
	Card *p_deck;
	p_deck = show_deck;
	int index;
	printf("%s\n", "Displaying deck:");
	for (index = CARD_INIT; index < DECK_SIZE; index++){
		++p_deck;
		display_card(*p_deck);
	}
	printf("\n");
	return;
}

/*----------------- display_hand ---------------------------------------------
 * function display_hand(Hand)
 *
 * Purpose: Displays a single hand from the Deck.
 *
 * @param Hand - Hand to be displayed 
 *
 * @return none. Is a print function.
-----------------------------------------------------------------------------*/
void display_hand(Hand showHand){
	int index;
	
	for(index = CARD_INIT; index <= CPH; index++){
		display_card(showHand.hand[index]);
	}
	return;
}

int get_largest(int *h_count, int *n_count, int *t_count, int *f_count,
		int *l_count, int r_count, int* h_card, int* n_card,
			int* t_card, int* f_card, int* l_card){
	int temp;
	temp = ZERO;
	if (*h_count > r_count){
		r_count = *h_count;
	}
	if (*n_count > r_count){
		r_count = *n_count;
		temp = *h_count;
		*h_count = *n_count;
		*n_count = temp;
	}
	if (*t_count > r_count){
		r_count = *t_count;
		temp = *h_card;
		*h_card = *t_card;
		*t_card = *n_card;
		*n_card = temp;
	}
	/* No need to test for fourth card- there's no way
 		it can be counted more than once. And if
		the low card counts twice, there is no fourth card */
	if (*l_count > r_count){
		r_count = *l_count;
		temp = *h_card;
		*h_card = *l_card;
		*l_card = *t_card;
		*t_card = *n_card;
		*n_card = temp;
	}	
	return r_count;
}

/*----------------- get_nameofrank -------------------------------------------
 * function get_nameofrank(int rank, char r_name[]) 
 *
 * Purpose: Receives an int, 1-13, that represents the rank of the card.
 * 	Also receives a pointer to type char[]. A switch statement
 * 	selects the rank name, which is then copied to the string 
 *	referenced by the pointer. Rank names are defined in enum
 *	in "poker.h" No value is returned, but the modified array
 *	is available to the calling function.
 *
 * @param int(rank) - rank as determined by the get_rank function
 *
 * @param char r_name[] - array of type char. Gets assigned the string
 * 	name of the card's rank. 
 *
 * @return none. Is a print function.
-----------------------------------------------------------------------------*/
void get_nameofrank(int rank, char r_name[]){
	switch(rank){
	case ACE:
		strcpy(r_name, "Ace");
		break;
	case TWO:
		strcpy(r_name, "Two");
		break;
	case THREE:
		strcpy(r_name, "Three");
		break;
	case FOUR:
		strcpy(r_name, "Four");
		break;
	case FIVE: 
		strcpy(r_name, "Five"); 
		break;
	case SIX:
		strcpy(r_name, "Six");
		break;
	case SEVEN:
		strcpy(r_name, "Seven");
		break;
	case EIGHT:
		strcpy(r_name, "Eight");
		break;
	case NINE:
		strcpy(r_name, "Nine");
		break;
	case TEN:
		strcpy(r_name, "Ten");
		break;
	case JACK:
		strcpy(r_name, "Jack");
		break;
	case QUEEN:
		strcpy(r_name, "Queen");
		break;
	case KING:
		strcpy(r_name, "King");
		break;
	default:
		printf("%s\n", "Invalid rank assignment.");
		break;
	}
}

/*----------------- get_nameofsuit -------------------------------------------
 * function get_nameofsuit
 *
 * Purpose: retrieves the string value associated with the card suit 
 *
 * @param - int suit - integer value 1-4 
 *
 * @return - none. Value is returned by pointer manipulation. 
 *
-----------------------------------------------------------------------------*/
void get_nameofsuit(int suit, char s_name[]){
	switch (suit){
	case CLUBS: 
		strcpy(s_name, "clubs");
		break;
	case DIAMONDS:
		strcpy(s_name, "diamonds");
		break;
	case HEARTS:
		strcpy(s_name, "hearts");
		break;
	case SPADES:
		strcpy(s_name, "spades");
		break;
	default:
		printf("%s\n", "Invalid suit assignment");			
		break;
	}
}

/*----------------- get_most ----------------------------------------------
 * function get_most(int, *int, *int)
 *
 * Purpose: Tracks when highest or second-highest card count changes 
 *
 * @param int(changed) - the new card
 * 	  int *most - the migh count
 * 	  int *n_most - the second high count
 *
 * @return void 
 *
-----------------------------------------------------------------------------*/
void get_most(int changed, int *most, int *n_most){
	if (changed > *most){
		*most = changed;
	}
	else
	if (changed > *n_most){
		*n_most = changed;
	} 
	return;
}

/*----------------- get_rank -------------------------------------------------
 * function get_rank(int i_d)
 *
 * Purpose: Returns an int used to represent the rank value of a struct card.
 * 	Simply returns the modulo of the id# of the card in the deck 
 * 	divided by the number of ranks (13). The highest card then has
 * 	modulo 0, so 13 is added to keep it highest.	
 *
 * @param int(i_d) - 1-52 id number of a card in a deck. That's 4 groups
 * 	of 13 ranks, so each number 1-13 represents a rank. 
 *
 * @return int- 1-10 represent the numbered ranks, 11 is "jack",
 * 	12 is "queen" and 13 is "king".
 *
-----------------------------------------------------------------------------*/
int get_rank(int i_d){
	int rank;
	rank = (i_d % NUM_RANKS);
	if (rank == ZERO){
		rank = KING;
	}
	return rank;
}

/*----------------- get_score -------------------------------------------------
 * function get_score(Hand)
 *
 * Purpose: Assigns a score to each hand. Score is assigned based on 
 * 	information at website
 * 	https://www.pokerstars.com/poker/games/rules/hand-rankings/ 
 *	Rankings in this order;
 *	Straight flush
 *	Four of a kind
 *	Full house
 *	Flush
 *	Straight
 *	Three of a kind
 *	Two pair
 *	One pair
 *	High card
 *	Each card receives a base score higher than the highest possible
 *	score of the next lower rank. That adds to the face
 *	value of the hand, and the total is returned.
 *	Cards that aren't part of a winning grouping are factored in as
 *	tiebreakers. These again are worked so that each grouping or card
 *	is worth more than all combined lower-ranking cards in the hand.
 *	This causes ridiculously high score values, especially in the
 *	lower-value hands, which may use all cards in the hand, but it
 *	prevents an aces-and-twos two-pair from being outranked by a
 *	high-card hand that contains a King, for one example. 
 *
 * @param - Hand - the Hand being scored 
 *
 * @return int - the score value of the hand 
 *
-----------------------------------------------------------------------------*/
long get_score(Hand aHand){
	int score;
	int straight;
	int flush;
	int h_index;
	int rank_count;

	score = ZERO;

	int high_card;
	int low_card;
	int next_card;
	int third_card;
	int fourth_card;
	int high_count;
	int next_count;
	int third_count;
	int fourth_count;
	int low_count;
	int suit_count;
	int *p_high;
	int *p_next;
	int *p_third;
	int *p_fourth;
	int *p_low;
	int *p_hcount;
	int *p_ncount;
	int *p_tcount;
	int *p_fcount;
	int *p_lcount;
	int *p_scount;

	p_high = &high_card;
	p_next = &next_card;
	p_third = &third_card;
	p_fourth = &fourth_card;
	p_low = &low_card;
	p_hcount = &high_count;
	p_ncount = &next_count;
	p_tcount = &third_count;
	p_fcount = &fourth_count;
	p_lcount = &low_count;
	p_scount = &suit_count;

	int sorted[CPH + CARD_INIT] = {ZERO, low_card, 
		fourth_card, third_card, next_card, high_card}; 
	int *p_sorted;
	p_sorted = sorted;

	high_card = next_card = third_card = fourth_card = high_count
		  = next_count = third_count = fourth_count = low_count  
			= rank_count = ZERO;
	low_card = DECK_SIZE;
	suit_count = CARD_INIT;

	/* Iterate through hand
  		Break down hand for:
  		- what is the high card in the hand
  		- how many times does each rank appear */
	p_sorted = sort_hand(sorted, aHand.hand, &high_count, &next_count, 
		&third_count, &fourth_count, &low_count, &suit_count);	
	low_card = *++p_sorted;
	fourth_card = *++p_sorted;
	third_card = *++p_sorted;
	next_card = *++p_sorted;
	high_card = *++p_sorted;
/*
	rank_count = get_largest(&high_count, &next_count, &third_count, 
		&fourth_count, &low_count, rank_count, &high_card,
			&next_card, &third_card, &fourth_card, &low_card);	
*/
	switch (high_count){
		case 4: 
			return isFourKind(high_card, low_card);
		case 3:
			if(low_count == TWO){
				return isFullHouse(high_card, low_card);
			}
			else
			return isThreeKind(high_card, next_card, low_card);
		case 2:
			if(next_count == TWO){
				return isTwoPair(high_card, 
					next_card, low_card);
			}
			else
			return isPair(high_card, next_card, third_card,
					low_card);	
		case 1:
			if (hasStraight(sorted) == TRUE){
				if(hasFlush(suit_count) == TRUE){
					return isStraightFlush(low_card);
				}
				else
				return isStraight(low_card);
			}
			else
			if (hasFlush(suit_count) == TRUE){
				return isFlush(high_card, next_card, third_card,
					fourth_card, low_card);
			}
			else
			return isHighCard(high_card, next_card, third_card, 
				fourth_card, low_card);
		default:
			printf("%s", "logic error in getScore function");
	}
	return score;
}

/*----------------- get_suit -------------------------------------------------
 * function get_suit(int i_d)
 *
 * Purpose: Returns an int used to represent the suit value of a struct card.
 * 	Uses a homemade ceiling function to return a number 1-4.  
 *
 * @param int(i_d) - 1-52 id number of a card in a deck. Each set of 13
 * 	numbers represents a single suit. 
 *
 * @return int- 1 = "clubs", 2 = "diamonds", 3 = "hearts", 4 = "clovers".
 * 	No, wait, 4 = "spades" 
 *
-----------------------------------------------------------------------------*/
int get_suit(int i_d){
	int suit;
	suit = i_d / NUM_RANKS;
	if ((i_d % NUM_RANKS) == 0){	 
		return suit;	 
	}
	else
		return suit + 1; 
}

/*----------------- get_Winner ------------------------------------------------
 * function get_Winner 
 *
 * Purpose: Finds the highest score of the hands 
 *
 * @param - Hand[] - all Hands
 * 	int num_hands - number of players
 *
 * @return - int - ID# of the winning hand 
 *
-----------------------------------------------------------------------------*/
int get_Winner(int num_hands, Hand allHands[num_hands]){
	long high_score;
	int handex;
	int winner;
	high_score = winner = ZERO;
	for (handex = CARD_INIT; handex <= num_hands; handex++){
		if (allHands[handex].score > high_score){
			high_score = allHands[handex].score;
			winner = allHands[handex].hand_id;
		}	
	}
	return winner;
}

/*----------------- hasFlush -------------------------------------------------
 * function hasFlush(Hand)  
 *
 * Purpose: Marks when flush is detected 
 *
 * @param - Hand - the Hand to be tested 
 *
 * @return - int - TRUE (0) or FALSE (1) 
 *
-----------------------------------------------------------------------------*/
int hasFlush(int has_f){
	int bool_val = FALSE;
	if (has_f == CPH){
		bool_val = TRUE;
	}
	return bool_val; 
}

/*----------------- hasStraight ------------------------------------------------
 * function hasStraight(int[])  
 *
 * Purpose: Tests the hand for presence of a straight.
 * 	Function is passed an array of cards sorted low to high. Their
 * 	values are compared one by one against the counter of a for loop
 * 	that increments by one. If the value of the counter = the value of 
 * 	the card on every pass, it is a straight.
 *
 * @param - int *sorted[] - the sorted cards in a pointer array. 
 *
 * @return - int - TRUE (0) or FALSE (1) 
 *
-----------------------------------------------------------------------------*/
int hasStraight(int sorted[]){
	int *p_card;
	p_card = sorted;
	int count;
	int temp;
	if ((sorted[1] == ACE) && (sorted[2] == TEN)){
		temp = NUM_RANKS + CARD_INIT;  
		sorted[1] = sorted[2];
		sorted[2] = sorted[3];
		sorted[3] = sorted[4];
		sorted[4] = sorted[5];
		sorted[5] = temp;
	} 
	p_card = sorted;	
	for (count = *++p_card; count <= sorted[CPH]; count++, p_card++){
		if (count != *p_card){
			return FALSE;
		} 
	}
	return TRUE;
}

/*----------------- isFlush -------------------------------------------------
 * function isFlush(int, int, int, int, int)  
 *
 * Purpose: Calculates the score of a hand that is a flush. 
 *
 * @param - int pointer to the rank value of each card, in sorted order 
 *
 * @return - int - flush base value + weighted face card value 
 *
-----------------------------------------------------------------------------*/
long isFlush(int high_card, int next_card, int third_card, int fourth_card,
		int low_card){
	long score;
	/* Numbers are as calculated for isHighCard */
	score = (low_card) + (9 + (fourth_card * 13)) + ((169 * third_card)
		+ 140) + ((13 * 13 * 13 * next_card) + 2000)
		+ ((13 * 13 * 13 * 13 * high_card) + 28365); 
	score = (score + PAIR_BASE + TWO_PAIR_BASE + THREE_KIND_BASE 
			+ STRAIGHT_BASE + FLUSH_BASE); 
	printf("%s %ld\n", "Flush score:", score);
	return score;
}

/*----------------- isFourKind ------------------------------------------------
 * function isFourKind(int, int)  
 *
 * Purpose: Calculates the score of a four-of-a-kind hand. Follows scoring
 * 	pattern of lower-scoring hands.
 * 	Highest possible hand: 4K + Q
 * 	low card: 1-13
 * 	high card: 12 cards, 14-170
 * 	score is high card + low card + combined high scores of all lower-
 * 		ranked hands 
 * 	Adding all gives straight flush base = 183
 *
 * @param - int high - face value of the four of a kind
 * 	    int low - face value of tiebreaker card 
 *
 * @return - long - score + scores of all lower-ranked combinations
 *
-----------------------------------------------------------------------------*/
long isFourKind(int high, int low){
	long score;
	score = (13 * high + 14) + low;
	score = (score + PAIR_BASE + TWO_PAIR_BASE + THREE_KIND_BASE
		+ STRAIGHT_BASE + FLUSH_BASE + FULL_HOUSE_BASE
		+ FOUR_KIND_BASE); 
	printf("%s %ld\n", " Four of a kind score:", score);
	return score;
}

/*----------------- isFullHouse ----------------------------------------------
 * function isFullHouse(int, int)  
 *
 * Purpose: Calculates score of a hand containing a full house. Pattern similar
 * 	to those of lower-valued hands.
 *	Highest possible hand: 3K + 2Q
 *	low card: 1-13
 *	high card: 12 cards, 14 + 12 * high_card = 169 
 *	score is high card + low card + combined high scores of all 
 *		lower-ranked hands
 *	Adding all gives 183 = four of a kind base
 *
 * @param - int high_card - value of the three-card grouping of the hand 
 * 	    int low_card - value of the two-card grouping of the hand
 *
 * @return - int - base score for a full house + the suit value
 *
-----------------------------------------------------------------------------*/
long isFullHouse(int high_card, int low_card){
	int score;
	/* numbers derived in function description */
	score = (12 * high_card + 14) + 13;
	score = (score + PAIR_BASE + TWO_PAIR_BASE + THREE_KIND_BASE
			+ STRAIGHT_BASE + FLUSH_BASE + FULL_HOUSE_BASE);
	printf("%s %ld\n", "Full house score:", score);
	return score;
}

/*----------------- isHighCard ----------------------------------------------
 * function isHighCard(Hand)  
 *
 * Purpose:  
 *	Scoring: Every card in the hand is a potential tiebreaker, so they 
 *		all count. The highest possible hand of this type goes
 *		like this: K-Q-J-10-8 (as 9 would give a straight). The low
 *		card counts as face value, but each next higher card has to 
 *		multiply instead of adding, to guarantee that each combination
 *		gives a unique score. This is like exponential math in a 
 *		base number system where the base decreasese by 1 each time
 *		a card has been played
 *		low card: 8 cards
 *			- Not 9 cards, or would be a straight
 *		next card: 10 cards: 9 + 10 * 13 = 139 
 *		third: 11 cards: 140 + (11 * 13 * 13) = 1999
 *		fourth: 12 cards: 2000 + (12 * 13 * 13 * 13) = 28364
 *		fifth: 13 cards: 28365 + (13 + 13 * 13 * 13 * 13) = 399658
 *		Adding all together gives 430168 - will be base score for
 *			one pair
 *
 * @param - Hand - the Hand to be tested 
 *
 * @return - int - highest suit value in the hand 
 *
-----------------------------------------------------------------------------*/
long isHighCard(int high_card, int next_card, int third_card,
		int fourth_card, int low_card){
	long score;
	/* numbers are as calculated in function documentation */
	score = (low_card) + (9 + (fourth_card * 13)) + ((169 * third_card)
		+ 140) + ((13 * 13 * 13 * next_card) + 2000)
		+ ((13 * 13 * 13 * 13 * high_card) + 28365); 
	printf("%s %ld\n", "High card score:", score);
	return score; 
}

/*----------------- isPair ----------------------------------------------
 * function isPair(Hand)  
 *
 * Purpose: Calculates the score of a hand identified to contain one pair.
 * 	Lowest possible score is higher than highest possible score of a 
 * 	High Card hand - ensured by adding hand score on top of High Card
 * 	high score of 200,616.
 * 	Highest possible 1-pair hand: 2K - Q - J - 10
 * 	low card: 1-10
 * 	third card: 11 cards: 11 + (11 * 13) = 154 
 * 	next card: 12 cards: 154 + (12 * 169) = 2182
 * 	high card: 13 cards: 2182 + (13 * 13 * 13 * 13) = 30743
 * 	Adding all gives two pair base: 33089
 *
 * @param - Hand - the Hand to be tested 
long isPair(int high_card, int next_card, int *third_card, int *low_card
 *
 * @return - int - base value of a pair plus the suit value of the pair 
 *
-----------------------------------------------------------------------------*/
long isPair(int high_card, int next_card, int third_card, int low_card){
	int temp;
	long score;
	/* see function description for origin of these numbers */
	score = ((high_card * 13 * 13 * 13 + 2182) 
		+ (next_card * 13 * 13 + 154) + (third_card * 13 + 11)
		+ low_card);
	score = (PAIR_BASE + score);
	printf("%s %ld\n", "Pair score:", score);
	return score; 
}

/*----------------- isStraight -------------------------------------------------
 * function isStraight(int low_card)  
 *
 * Purpose: Calculates the score of a hand that contains a straight 
 * 	Highest possible hand: A + K + Q + J + 10. All 5 cards count, so
 * 	there are no tiebreakers.
 * 	Score: 1-10 + combined scores of lower hands
 *
 * @param - int - low_card - calculates value from the low card. 
 *
 * @return - long - low card + base score 
 *
-----------------------------------------------------------------------------*/
long isStraight(int low_card){
	long score;
	score = (low_card + PAIR_BASE + TWO_PAIR_BASE + THREE_KIND_BASE
		+ STRAIGHT_BASE); 
	printf("%s %ld\n", "Straight score:", score);
	return score; 
}

/*----------------- isStraightFlush ------------------------------------------
 * function isStraightFlush(int)  
 *
 * Purpose: Calculates the score of a straight flush
 * 	Highest possible hand: A + K + Q + J + 10
 * 	returns low card: 1-10
 * 	score = low card + combination of all lower-value hands 
 *	  
 * @param - int - low_card - the low card of the straight 
 * 
 * @return - long - returns the base value of a straight flush
 * 			plus the low suit of the hand 
 *
-----------------------------------------------------------------------------*/
long isStraightFlush(int low_card){
	long score;
	score = (low_card + FOUR_KIND_BASE + FULL_HOUSE_BASE + FLUSH_BASE
		+ STRAIGHT_BASE + THREE_KIND_BASE + TWO_PAIR_BASE 
			+ PAIR_BASE + STRAIGHT_FLUSH_BASE); 
	printf("%s %ld\n", "Straight flush score:", score);
	return score; 
}

/*----------------- isThreeKind ----------------------------------------------
 * function isThreeKind(Hand)  
 *
 * Purpose: returns the score of a hand containing a three-of-a-kind 
 *
 * @param - int - the rank value of the three-of-a-kind
 * 	and two tiebreaker cards 
 * 	See isHighCard for further details
 * 	Highest possible hand: 3K + Q + J
 * 	low card: 1-11
 * 	next card: 12 faces: 12 + 12 * 13 = 168
 *	high card: 13 faces: 169 + 13 * 13 * 13 = 2366 
 *	Adding all gives straight base: 2545
 *
 * @return - long - the score of the hand above the highest possible scores
 * 	of all lower hands 
 * 	200,636 + 22,330 + 1885 = 224851
 *
-----------------------------------------------------------------------------*/
long isThreeKind(int h_card, int n_card, int l_card){
	long score;
	/* See function description for derivation of these numbers */
	score = ((h_card * 169) + 169) + ((n_card * 13) + 12) + l_card;
	score = (score + PAIR_BASE + TWO_PAIR_BASE + THREE_KIND_BASE);
	printf("%s %ld\n", "Three of a kind score:", score);
	return score; 
}

/*----------------- isTwoPair ----------------------------------------------
 * function isTwoPair(Hand)  
 *
 * Purpose: calculates the score of a hand with two pairs.
 * 	    See isHighCard and isPair for details on the scoring.	 
 * 	    Highest possible hand: 2K + 2Q + J
 * 	    low card: 1-11
 * 	    next card: 12 cards: 12 + 12 * 13 = 168
 * 	    high card: 13 cards: 169 + 13 * 13 * 13 = 2366
 * 	    Adding all gives Three of a kind base: 2545
 *
 * @param - int high_card - higher of the two pairs
 * 	    int next_card - lower of the two pairs
 * 	    int low_card - tiebreaker card 
 *
 * @return - long - score for the hand + highest possible score for
 *	    a single-pair hand + highest score for a high-card hand,
 *	    200,636 + 22,330 = 222,966 
 *
-----------------------------------------------------------------------------*/
long isTwoPair(int high_card, int next_card, int low_card){
	long score;
	/* numbers as derived in function description */
	score = (((high_card * 169) + 169) + ((next_card * 12) + 12)
		+ low_card);
	score = (score + PAIR_BASE + TWO_PAIR_BASE);
	printf("%s %ld\n", "Two pair score:", score);
	return score; 
}

/*----------------- shuffle_deck ---------------------------------------------
 * function shuffle_deck(Deck o_deck)
 *
 * Purpose: Is passed a pointer to the original deck of cards and returns
 * 	it as a new, shuffled deck
 * 	Is an implementation of the Fisher-Yates shuffle as referenced in
 * 	assignment handout at webpage
 * 	https://en.wikipedia.org/wiki/
 *		Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
 *
 * @param Deck(o_deck) - previously generated deck is passed in 
 *
 * @return Card* - pointer to the first array element of shuffled deck 
 *
-----------------------------------------------------------------------------*/
Card* shuffle_deck(Deck o_deck){
	Card *p_deck;
	p_deck = o_deck;
	int s_index;	
	int randm;
	Card temp;
	for (s_index = DECK_SIZE; s_index > CARD_INIT; ){
		--s_index;
		randm = (rand() % s_index);
		if(randm == ZERO){
			randm = CARD_INIT;
		}
		temp = o_deck[randm];	
		o_deck[randm] = o_deck[s_index];
		*(p_deck + s_index)  = o_deck[s_index] = temp;
	}
	return p_deck;
}

/*----------------- sort_hand ------------------------------------------------
 * function sort_hand(Card[]) 
 *
 * Purpose: Sorts the cards in order. Rearranges them by pointer passing. 
 *
 * @param - Card[] hnd - the hand to be ordered 
 *
 * @return - *int - returns pointer to the first element of the reordered array
 * 	of Cards 
 *
-----------------------------------------------------------------------------*/
int* sort_hand(int sorted[], Card hand[], int *high_count, 
		int *next_count, int *third_count, int *fourth_count, 
			int *low_count, int *suit_count){
	int rank_count;
	int index;
	int most;
	int next_most;
	int temp;

	int high_card;
	int next_card;
	int third_card;
	int fourth_card;
	int low_card;

	int *p_high;
	int *p_next;
	int *p_third;
	int *p_fourth;
	int *p_low;

	rank_count = temp = most = next_most = high_card = next_card
		= third_card = fourth_card = ZERO;
	low_card = NUM_RANKS;
	for (index = CARD_INIT; index <= CPH; index++){
		if (hand[index].suit 
			== hand[(index - CARD_INIT)].suit){
				*suit_count = *suit_count + 1;
		}
		if (hand[index].rank == high_card){
			*high_count += 1;
			get_most(*high_count, &most, &next_most); 
		} 
		else
		if (hand[index].rank > high_card){
			/* New high card */
			if((low_card == NUM_RANKS) && 
					(*high_count > 0)){
				/* if there's a high card
 * 					but not a low card */ 
				low_card = high_card;
				*low_count = *high_count;
			}
			else{
				/* add the new high card and push any
 * 					existing cards down the ranks */
				if(third_card > ZERO){
					fourth_card = third_card;
					*fourth_count = *third_count;
				}
				if(next_card > ZERO){
					third_card = next_card;
					*third_count = *next_count;
				}
				next_card = high_card;
				*next_count = *high_count;
			}
			high_card = hand[index].rank;
			*high_count = CARD_INIT;
			get_most(*high_count, &most, &next_most); 
		}
		else
		if (hand[index].rank < low_card){
			/* there's a new low card */
			if (*low_count > 0){
				/* if there's already a low card:
 * 					move it up the line */
				if (*next_count == ZERO){  
					*next_count = *low_count;
					next_card = low_card;	
				}
				else
				if ((*third_count == ZERO)
						&& (next_count > ZERO)){
					*third_count = *low_count;
					third_card = low_card;
				}
				else
				if ((*fourth_count == ZERO)
						&& (third_count > ZERO)){
					*fourth_count = *low_count;
					fourth_card = low_card;
				}
			}
			low_card = hand[index].rank;
			*low_count = CARD_INIT;
			get_most(*low_count, &most, &next_most); 
		}
		else
		if (hand[index].rank == next_card){
			*next_count += 1; 
			get_most(*next_count, &most, &next_most); 
		}
		else
		if (hand[index].rank == third_card){
			*third_count += 1; 
			get_most(*third_count, &most, &next_most); 
		}
		else
		if (hand[index].rank == low_card){
			*low_count += 1; 
			get_most(*low_count, &most, &next_most); 
		}
		else
		if ((hand[index].rank > next_card)
			&& (hand[index].rank < high_card)){
			if(third_card > ZERO){
				fourth_card = third_card;
				*fourth_count = *third_count;
			}
			third_card = next_card;
			*third_count = *next_count;
			next_card = hand[index].rank;
			*next_count = CARD_INIT;	
			get_most(*next_count, &most, &next_most); 
		 }
		else
		if ((hand[index].rank > third_card)
				&& (hand[index].rank < next_card)){
			fourth_card = third_card;
			*fourth_count = *third_count;
			third_card = hand[index].rank;
			*third_count = CARD_INIT;
			get_most(*third_count, &most, &next_most); 
		} 
		else
		if ((hand[index].rank > fourth_card)
				&& (hand[index].rank < third_card)){
			fourth_card = hand[index].rank;
			*fourth_count = CARD_INIT;
			get_most(*fourth_count, &most, &next_most); 
		}
		
	}
	/* Reorder the cards by groupings */
	/* First find which occurs most & 2nd most */
	/* A five-card hand allows at most two groupings of more than one card*/
	
	/* Now reorder their positions */
	if((most == 2) && (next_most == 2)){
		/* hand has two pairs */
		if(*high_count != most){
			/* other two values are the pairs */
			if(*next_count == most){
				temp = high_card;
				high_card = next_card;
				*low_count = *high_count;
				*high_count = *next_count;
				next_card = low_card;
				*next_count = *low_count;
				low_card = temp;
			}
		}
		else
		if(*next_count != most){
			temp = next_card;
			next_card = low_card;
			*low_count = *next_count;
			*next_count = most;
			low_card = temp;		
		}
	}
	else 
	if(most == 4){
		if(*high_count != most){
			temp = high_card;
			high_card = low_card;
			*low_count = *high_count;
			*high_count = most;
			low_card = temp;
		}
	}
	else
	if(most == 3){
		if(next_most == 2){
		/* full house */
			if(*high_count != most){
				/* low card is the three of a kind,
 * 					switch high and low */
				temp = high_card;
				high_card = low_card;
				*low_count = *high_count;
				*high_count = most;
				low_card = temp;
			}
		}
		else
		if(*high_count != most){
			/* if high card is most
 * 				then hand is already in order */
			if(*next_count != most){
				/* low card is most */
				/* reorder low-high-next */
				temp = high_card;
				high_card = low_card;
				low_card = next_card;
				*low_count = *next_count;
				*next_count = *high_count;
				*high_count = most;		
				next_card = temp;
			}
			else 
				/* next card is most */
				/* reorder next-high-low */
				temp = high_card;
				*next_count = *high_count;
				*high_count = most;
				high_card = next_card;
				next_card = temp;
			
		}
	}
	else
	if((most == 2) && (next_most == 1)){
		/* One pair */
		/* Make pair the high card, others follow in order */
		if(*high_count != most){
			/* Nothing to do if high card is the pair */
			if(*next_count == most){
				temp = high_card;
				high_card = next_card;
				*next_count = *high_count;
				*high_count = most;
				next_card = temp;
			}
			else
			if(*third_count == most){
				temp = high_card;
				high_card = third_card;
				*third_count = *next_count;
				*next_count = *high_count;
				*high_count = most;
				third_card = next_card;
				next_card = temp;
			}
			else
			if(*low_count == most){
				temp = high_card;
				high_card = low_card;
				*low_count = *third_count;
				*third_count = *next_count;
				*next_count = *high_count;
				*high_count = most;
				low_card = third_card;
				third_card = next_card;
				next_card = temp;
			}
		}
	}	
	int *p_sc;
	sorted[1] = low_card;
	sorted[2] = fourth_card;
	sorted[3] = third_card;
	sorted[4] = next_card;
	sorted[5] = high_card;
	p_sc = sorted;
	return p_sc;
}
	

/*----------------- validate -------------------------------------------------
 * function validate(int, int) 
 *
 * Purpose: Verifies that user input is within proper boundaries:
 * 	- the number of players must be between 1-7. Values outside this range 
 * 	  display an error and require relaunch.
 * 	- the number of cards per hand is fixed at 5 per stud poker rules.
 * 	  Other input values will generate a message, but they will not
 * 	  impact program operation.
 *
 * @param - int num_hands - user-input number of players
 * 	    int cph - user-input number of cards per hand 
 *
 * @return - int - TRUE or FALSE - enum-defined int values, 0 or 1  
 *
-----------------------------------------------------------------------------*/
int validate(int num_hands, int cph){
	if ((num_hands < MIN_PLYRS) || (num_hands > MAX_PLYRS)){
		printf("%s", "Improper input. Enter a number of players ");
		printf("%s %d", "between ", MIN_PLYRS);
		printf("%s %d %s\n", " and ", MAX_PLYRS, ".");
		return FALSE;
	}
	if (cph != CPH){
		printf("%s", "Setting number of cards to a hand at ");
		printf("%d %s\n", CPH, ".");
	}
	return TRUE;
}

/*----------------- validate_num_args ------------------------------------------
 * function validate_num_args(int)
 *
 * Purpose: Verifies that user-input number of arguments is correct  
 *
 * @param - int num_args - should be 3: the program itself, and the
 * 	two input values
 *
 * @return - int - TRUE or FALSE - enum-defined int values, 0 or 1  
 *
-----------------------------------------------------------------------------*/
int validate_num_args(int n_args){
	if (n_args != ARGS_EXP){
		printf("%s\n", "Improper input.");
		printf("%s", "Please enter a number of players ");
		printf("%s %d %s", "between ", MIN_PLYRS, " and ");
		printf("%d %s\n", MAX_PLYRS, ",");
		printf("%s", "followed by a number of cards per hand, ");
		printf("%s %d\n","which is required to be ", CPH );
		return FALSE;
	}
	else
		return TRUE;
}

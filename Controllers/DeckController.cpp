/* To ensure that the your cards are ordered the same way as
the given program, use this shuffling algorithm.

CARD_COUNT is the constant 52
cards_ is an array of pointers to cards
*/

#define CARD_COUNT 52

#include <random>
#include <iostream>
#include "DeckController.h"

DeckController::DeckController(): deckModel(new DeckModel())
{
};

DeckController::~DeckController()
{
    delete deckModel;
};

void DeckController::shuffle(int seed = 0){
    static std::mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = deckModel->cards_[n];
		deckModel->cards_[n] = deckModel->cards_[k];
		deckModel->cards_[k] = c;
	}
}

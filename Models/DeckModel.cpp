#include <random>
#include <iostream>
#include "DeckModel.h"
#include "Card.h"
#include "CardType.h"

DeckModel::DeckModel()
{
    for (unsigned int i = 0; i < SUIT_COUNT; ++i){
        for (unsigned int j = 0; j < RANK_COUNT; ++j) {
            cards_.push_back(new Card((Suit)i, (Rank)j));
        }
    }
}

DeckModel::~DeckModel()
{
    for (unsigned int i = 0; i < cards_.size(); ++i) {
        delete cards_[i];
    }
}

void DeckModel::shuffle(unsigned long seed) {
    static std::mt19937 rng(seed);

    int n = CARD_COUNT;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

std::vector<Card *> DeckModel::getCards() const {
    return cards_;
}


#include <random>
#include "DeckModel.h"

DeckModel::DeckModel()
{
    for (unsigned int i = 0; i < SUIT_COUNT; ++i)
    {
        for (unsigned int j = 0; j < RANK_COUNT; ++j) 
        {
            cards_.push_back(std::make_shared<Card>((Suit)i, (Rank)j));
        }
    }
}

DeckModel::~DeckModel()
{
}

void DeckModel::shuffle(unsigned long seed) 
{
    static std::mt19937 rng(seed);

    int n = CARD_COUNT;

    while ( n > 1 ) 
    {
        int k = (int) (rng() % n);
        --n;
        std::shared_ptr<Card> c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

const std::vector<std::shared_ptr<Card> > * DeckModel::getCards() const
{
    return &cards_;
}


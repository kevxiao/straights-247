#include <random>
#include "DeckModel.h"

// create deck model and add in all the cards in order
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

// default destructor
DeckModel::~DeckModel()
{
}

// shuffle cards in deck using the seed
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

// get the list of cards in the deck in order
const std::vector<std::shared_ptr<Card> > * DeckModel::getCards() const
{
    return &cards_;
}

// reset cards in deck to original ordered state
void DeckModel::reset()
{
    for (unsigned int i = 0; i < SUIT_COUNT; ++i)
    {
        for (unsigned int j = 0; j < RANK_COUNT; ++j)
        {
            cards_.push_back(std::make_shared<Card>((Suit)i, (Rank)j));
        }
    }
}

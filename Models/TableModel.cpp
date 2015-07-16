#include <map>
#include "TableModel.h"

// create table model by create a map of 4 suits
TableModel::TableModel() 
{
    for (int i = 0; i < SUIT_COUNT; ++i) 
    {
        cardsOnTable_.insert(std::make_pair<Suit, std::map<Rank, std::shared_ptr<Card> > >((Suit)i, std::map<Rank, std::shared_ptr<Card> >()));
    }
}

//default destructor
TableModel::~TableModel() 
{
}

// clear all cards from the table
void TableModel::resetTable() 
{
    for (auto it = cardsOnTable_.begin(); it != cardsOnTable_.end(); ++it) 
    {
        it->second.clear();
    }
}

// add a card to the table
void TableModel::addCardToTable(std::shared_ptr<Card> card) 
{
    cardsOnTable_.at(card->getSuit()).insert(std::pair<Rank, std::shared_ptr<Card> >(card->getRank(), card));
}

// get all the cards on the table
const std::map<Suit, std::map<Rank, std::shared_ptr<Card> > > * TableModel::getCardsOnTable() const
{
    return &cardsOnTable_;
}


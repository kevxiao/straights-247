#include <map>
#include "TableModel.h"
#include "Card.h"
#include "CardType.h"

TableModel::TableModel() {
    for (int i = 0; i < SUIT_COUNT; ++i) {
        cardsOnTable_.insert(std::make_pair<Suit, std::map<Rank, Card *> >((Suit)i, std::map<Rank, Card *>()));
    }
}

TableModel::~TableModel() {
}

void TableModel::resetTable() {
    for (auto it = cardsOnTable_.begin(); it != cardsOnTable_.end(); ++it) {
        it->second.clear();
    }
}

void TableModel::addCardToTable(Card *card) {
    cardsOnTable_.at(card->getSuit()).insert(std::pair<Rank, Card *>(card->getRank(), card));
}

std::map<Suit, std::map<Rank, Card *>> TableModel::getCardsOnTable() const {
    return cardsOnTable_;
}


#include "CardType.h"
#include <string>
#include <cassert>
using namespace std;

CardType::CardType(Suit s, Rank r)
{
	suit_ = s;
	rank_ = r;
}

CardType::CardType(std::string cardTypeinString)
{
    string suits = "CDHS", ranks = "A234567891JQK";
	
    //Read in the rank, make sure it's valid
    rank_ = (Rank)ranks.find( cardTypeinString.at(0) );
    assert ( rank_ != string::npos );
	
    //If it's a 10, make sure the 2nd character is a 0
    if ( rank_ == TEN ){
        assert(cardTypeinString.at(1) == '0');
        cardTypeinString.at(1) = cardTypeinString.at(2);
    }
	
    //Read in the suit, make sure it's valid
    suit_ = (Suit)suits.find( cardTypeinString.at(1) );
    assert ( suit_ != string::npos );
}

Suit CardType::getSuit() const
{
	return suit_;
}

Rank CardType::getRank() const
{
	return rank_;
}

bool operator==(const CardType &a, const CardType &b)
{
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const CardType &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

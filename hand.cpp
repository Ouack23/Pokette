#include "hand.h"
#include "card.h"
#include <QString>
#include <iostream>
#include "exception.h"

Hand::Hand(Card Card1, Card Card2):
	Cards(std::vector<Card>(2)),
	HandException(Exception("Hand")) {
	Cards.at(0).setCard(Card1);
	Cards.at(1).setCard(Card2);
}

Hand::~Hand() {

}

Card Hand::getCard(const int n) const {
	return Cards.at(n);
}

Card Hand::getOtherCard(const int n) const {
	if (n == 0) return Cards.at(1);
	else return Cards.at(0);
}

std::vector<Card> Hand::getCards() const {
	return Cards;
}

bool Hand::setCard(const int n, const Card MyCard) {
	if (getOtherCard(n) == MyCard) {
		HandException.throwException("setCard(int n, Card MyCard)", "Cannot have the same card twice in hand");
		return false;
	}
	else {
		Cards.at(n).setCard(MyCard);
		if(getCard(n) != MyCard) {
			HandException.throwException("Hand::setCard(const int, const Card)", "Card hasn't been correctly set !");
			return false;
		}
		else return true;
	}
}

void Hand::setHand(const Hand h) {
	for(unsigned int i = 0; i < h.getCards().size(); i++)
		Cards.at(i).setCard(h.getCard(i));
}

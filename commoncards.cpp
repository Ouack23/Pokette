#include "commoncards.h"
#include "card.h"
#include "hand.h"
#include "functions.h"
#include <vector>
#include <iostream>
#include <QString>

CommonCards::CommonCards(std::vector<Card> cards):
	TableCards(cards),
	CommonCardsException(Exception("CommonCards"))
{

}

CommonCards::~CommonCards() {

}

std::vector<Card> CommonCards::getFlop() const {
	std::vector<Card> result;
	std::vector<Card>::const_iterator i;

	for (i = TableCards.begin(); i <= TableCards.begin()+3; i++)
		result.push_back(*i);

	return result;
}

Card CommonCards::getTurn() const {
	return TableCards.at(3);
}

Card CommonCards::getRiver() const {
	return TableCards.at(4);
}

Card CommonCards::getCard(const unsigned int n) const {
	if (n >= getCards().size()) {
		CommonCardsException.throwException("getCard(const unsigned int n)", "n out of bound");
		return Card();
	}
	else return TableCards.at(n);
}

std::vector<Card> CommonCards::getCards() const {
	std::vector<Card> result;
	std::vector<Card>::const_iterator i;

	for (i = TableCards.begin(); i != TableCards.end(); i++)
		result.push_back(*i);

	return result;
}

bool CommonCards::setCard(const unsigned int n, Card MyCard) {
	if (n >= getCards().size()) {
		CommonCardsException.throwException("setCard(const int n, Card MyCard)", "n out of bound");
		return false;
	}
	else {
		if (isAlreadyOut(MyCard)) {
			CommonCardsException.throwException("setCard(const int n, Card MyCard)", "Card already out !");
			return false;
		}
		else return TableCards.at(n).setCard(MyCard);
	}
}

bool CommonCards::isAlreadyOut(const Card c) const {
	bool result = false;

	std::vector<Card>::iterator i;
	std::vector<Card> allCards = getCards();

	for (i = allCards.begin(); i != allCards.end(); i++) {
		if(*i == c) result = true;
	}

	return result;
}

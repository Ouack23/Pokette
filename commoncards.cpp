#include "commoncards.h"
#include "card.h"
#include "hand.h"
#include "functions.h"
#include "combinaison.h"
#include <vector>
#include <iostream>
#include <QString>

CommonCards::CommonCards(std::vector<Card> cards, Hand Myhand):
	TableCards(cards),
	HandCards(Myhand),
	currentCombin(),
	CommonCardsException(Exception("CommonCards"))
{

}

CommonCards::~CommonCards() {

}

std::vector<Card> CommonCards::getFlop() const {
	std::vector<Card> result;
	std::vector<Card>::const_iterator i;

	for (i = TableCards.begin(); i <= TableCards.begin()+3; i++) {
		result.push_back(*i);
	}

	return result;
}

Card CommonCards::getTurn() const {
	return TableCards.at(3);
}

Card CommonCards::getRiver() const {
	return TableCards.at(4);
}

Hand CommonCards::getHand() const {
	return HandCards;
}

Card CommonCards::getCard(const unsigned int n) const {
	if (n > getCards().size()) {
		CommonCardsException.throwException("getCard(const int n", "n out of bound");
		return Card();
	}
	else if (n <= 1) return HandCards.getCard(n);
	else return TableCards.at(n-2);
}

std::vector<Card> CommonCards::getCards() const {
	std::vector<Card> result;
	std::vector<Card>::const_iterator i;
	std::vector<Card> hand = HandCards.getCards();

	for (i = TableCards.begin(); i != TableCards.end(); i++)
		result.push_back(*i);
	for (i = hand.begin(); i != hand.end(); i++)
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
		else {
			if (n < 2) HandCards.setCard(n, MyCard);
			else TableCards.at(n-2) = MyCard;
			updateCombinaison();
			return true;
		}
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

void CommonCards::setCombin(const Combinaison c) {
	currentCombin = c;
}

void CommonCards::updateCombinaison() {
	std::vector<Card> allCards = getCards();
	std::vector<std::pair<unsigned int, unsigned int>> allCardsDifferentValues = getDifferentValues(allCards);
	std::vector<std::pair<QChar, unsigned int>> allCardsDifferentColors = getDifferentColors(allCards);
	std::vector<unsigned int> allCardsValues(0);
	unsigned int isStraight(0);
	Combinaison tmpBest;

	for(std::vector<std::pair<QChar, unsigned int >>::iterator i = allCardsDifferentColors.begin(); i != allCardsDifferentColors.end(); i++) {
		if((*i).second >= 5) {
			tmpBest.setComb(Combinaison::couleur);
			tmpBest.setValue(1, getMaxValueOfColor((*i).first, allCards));
		}
	}

	for(std::vector<std::pair<unsigned int, unsigned int>>::iterator i = allCardsDifferentValues.begin(); i != allCardsDifferentValues.end(); i++) {
		if((*i).first != Card::defaultValue) {
			switch((*i).second) {
			case 1:
				if(tmpBest.getCombinValue() == Combinaison::carteHaute &&
						tmpBest.getValue(1) < (*i).first)
					tmpBest.setValue(1, (*i).first);
				break;

			case 2:
				if(tmpBest.getCombinValue() == Combinaison::carteHaute) {
					tmpBest.setComb(Combinaison::paire);
					tmpBest.setValue(1, (*i).first);
				}
				else if(tmpBest.getCombinValue() == Combinaison::paire) {
					tmpBest.setComb(Combinaison::doublePaire);
					tmpBest.setValue(2, (*i).first);
					tmpBest.sortValues();
				}
				else if(tmpBest.getCombinValue() == Combinaison::doublePaire) {
					if(tmpBest.getValue(1) < (*i).first) {
						tmpBest.swapValues();
						tmpBest.setValue(1, (*i).first);
					}
					else if(tmpBest.getValue(2) < (*i).first) {
						tmpBest.setValue(2, (*i).first);
					}
				}
				else if(tmpBest.getCombinValue() == Combinaison::brelan) {
					tmpBest.setComb(Combinaison::full);
					tmpBest.setValue(2, (*i).first);
				}
				else if(tmpBest.getCombinValue() == Combinaison::full) {
					if(tmpBest.getValue(2) <= (*i).first)
						tmpBest.setValue(2, (*i).first);
				}
				break;

			case 3:
				if(tmpBest.getCombinValue() == Combinaison::paire ||
						tmpBest.getCombinValue() == Combinaison::doublePaire) {
					tmpBest.setComb(Combinaison::full);
					tmpBest.swapValues();
					tmpBest.setValue(1, (*i).first);
				}
				else if(tmpBest.getCombinValue() == Combinaison::carteHaute) {
					tmpBest.setComb(Combinaison::brelan);
					tmpBest.setValue(1, (*i).first);
				}
				else if(tmpBest.getCombinValue() == Combinaison::brelan &&
						tmpBest.getValue(1) < (*i).first)
					tmpBest.setValue(1, (*i).first);
				break;

			case 4:
				if(tmpBest.getCombinValue() < Combinaison::carre) {
					tmpBest.setComb(Combinaison::carre);
					tmpBest.setValue(1, (*i).first);
				}
				break;

			default:
				CommonCardsException.throwException("updateCombinaison()", "Impossible number of card found !");
				break;
			}

			allCardsValues.push_back((*i).first);
		}
	}

	isStraight = lookForStraight(allCardsValues);

	if(isStraight != 0 && tmpBest.getCombinValue() < Combinaison::quinte) {
		tmpBest.setComb(Combinaison::quinte);
		tmpBest.setValue(1, isStraight);
	}
	else if(isStraight != 0 && tmpBest.getCombinValue() == Combinaison::couleur) {
		tmpBest.setComb(Combinaison::quinteFlush);
		tmpBest.setValue(1, isStraight);
	}
	currentCombin = tmpBest;
}

QString CommonCards::getCurrentCombinaisonQString() const {
	QString result;

	switch(currentCombin.getCombinValue()) {
	case Combinaison::carteHaute:
		result.append("Carte haute ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::paire:
		result.append("Paire de ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::doublePaire:
		result.append("Deux paires de ");
		result.append(currentCombin.getValueString(1));
		result.append(" et ");
		result.append(currentCombin.getValueString(2));
	break;

	case Combinaison::brelan:
		result.append("Brelan de ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::quinte:
		result.append("Quinte à ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::couleur:
		result.append("Flush à ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::full:
		result.append("Full aux ");
		result.append(currentCombin.getValueString(1));
		result.append(" par les ");
		result.append(currentCombin.getValueString(2));
	break;

	case Combinaison::carre:
		result.append("Carré de ");
		result.append(currentCombin.getValueString(1));
	break;

	case Combinaison::quinteFlush:
		result.append("Quinte Flush à ");
		result.append(currentCombin.getValueString(1));
	break;

	default:
		CommonCardsException.throwException("getCurrentCombinaisonQString()", "unknown combinaison !");
	break;
	}

	return result;
}

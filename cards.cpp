#include "cards.h"
#include "functions.h"
#include "card.h"

Cards::Cards():
	MyCommonCards(CommonCards()),
	Combinaisons(),
	CardsException(Exception("Cards"))
{
	Hands = std::vector<Hand>();
}

std::vector<Hand> Cards::getHands() const {
	return Hands;
}

std::vector<Card> Cards::getCommonCardsObjects() const {
	return MyCommonCards.getCards();
}

CommonCards Cards::getCommonCards() const {
	return MyCommonCards;
}

std::vector<Card> Cards::getAllCards() const {
	std::vector<Card> result = Hands.at(0).getCards();
	std::vector<Card> tmp = MyCommonCards.getCards();

	for(std::vector<Card>::const_iterator j = tmp.begin(); j != tmp.end(); j++)
		result.push_back(*j);

	for(std::vector<Hand>::const_iterator i = Hands.begin()+1; i != Hands.end(); i++) {
		tmp = (*i).getCards();
		for(std::vector<Card>::const_iterator j = tmp.begin(); j != tmp.end(); j++)
			result.push_back(*j);
	}

	return result;
}

std::vector<Combinaison> Cards::getCombinaisons() const {
	return Combinaisons;
}

Combinaison Cards::getCombinaisonOfHand(const unsigned int i) const {
	if(i >= Hands.size()) {
		CardsException.throwException("getCombinaisonOfHand(const unsigned int)", "i > size of Hand");
		return Combinaison();
	}

	else return Combinaisons.at(i);
}

std::vector<std::pair<Hand, Combinaison>> Cards::getAllHandsAndCombinaisons() const {
	std::vector<std::pair<Hand, Combinaison>> result;

	for(unsigned int i = 0; i < Hands.size(); i++)
		result.push_back(std::pair<Hand, Combinaison> (Hands.at(i), Combinaisons.at(i)));

	return result;
}

std::vector<Card> Cards::getCardsFromHandAndCommonCards(const unsigned int i) const {
	std::vector<Card> result = Hands.at(i).getCards();
	std::vector<Card> myCommonCardsVector = MyCommonCards.getCards();

	for(std::vector<Card>::iterator it = myCommonCardsVector.begin(); it != myCommonCardsVector.end(); it++) {
		result.push_back(*it);
	}

	return result;
}

void Cards::setHand(const Hand h, const unsigned int i) {
	if (i < Hands.size())
		Hands.at(i).setHand(h);
	else
		CardsException.throwException("setHand(const Hand, const unsigned int)", "int > size of Hands");
}

void Cards::addHand(const Hand h) {
	Hands.push_back(h);
}

void Cards::addCombinaison(const Combinaison c) {
	Combinaisons.push_back(c);
}

bool Cards::setCard(const unsigned int i, const Card c) {
	if(i >= getAllCards().size())
		return false;
	else {
		switch(i) {
		case 0:
		case 1:
			return Hands.at(0).setCard(i, c);
		break;

		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			return MyCommonCards.setCard(i-2, c);
		break;

		case 7:
		case 8:
			return Hands.at(1).setCard(i-7, c);
		break;

		case 9:
		case 10:
			return Hands.at(2).setCard(i-9, c);
		break;

		case 11:
		case 12:
			return Hands.at(3).setCard(i-11, c);
		break;

		case 13:
		case 14:
			return Hands.at(4).setCard(i-13, c);
		break;

		default:
			return Hands.at(5).setCard(i-15, c);
		break;
		}
	}
	return true;
}

bool Cards::setCommonCard(const unsigned int i, const Card c) {
	return MyCommonCards.setCard(i, c);
}

void Cards::setCombinaisonOfHand(const Combinaison c, const unsigned i) {
	Combinaisons.at(i).setComb(c.getCombinValue());
}

void Cards::updateCombinaisons() {
	for(unsigned int i = 0; i < Hands.size(); i++)
		updateCombinaison(i);
}

void Cards::updateCombinaison(unsigned int i) {
	std::vector<Card> allCards = this->getCardsFromHandAndCommonCards(i);
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
				if(tmpBest.getCombinValue() == Combinaison::carteHaute && tmpBest.getValue(1) < (*i).first)
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
				CardsException.throwException("updateCombinaison()", "Impossible number of card found !");
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

	Combinaisons.at(i).setComb(tmpBest.getCombinValue());
}

#include "cards.h"
#include "functions.h"

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

void Cards::setCombinaisonOfHand(const Combinaison c, const unsigned i) {

}

bool Cards::setCommonCard(const unsigned int i, const Card c) {
	return MyCommonCards.setCard(i, c);
}

void Cards::updateCombinaisons() {
	for(std::vector<Hand>::iterator i = Hands.begin(); i != Hands.end(); i++)
		this->updateCombinaison(*i);
}

std::vector<Card> Cards::getCardsFromHandAndCommonCards(const Hand h) const {
	std::vector<Card> result = h.getCards();
	std::vector<Card> tmp = MyCommonCards.getCards();

	for(std::vector<Card>::iterator i = tmp.begin(); i != tmp.end(); i++)
		result.push_back(*i);

	return result;
}

void Cards::updateCombinaison(const Hand h) {
	std::vector<Card> allCards = this->getCardsFromHandAndCommonCards(h);
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
}

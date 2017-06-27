#include <vector>
#include "card.h"
#include "combinaison.h"
#include "functions.h"
#include "hand.h"

std::vector<unsigned int> CardVectorToValuesVector(const std::vector<Card> MyCards) {
	std::vector<Card>::const_iterator i;
	std::vector<unsigned int> result;

	for(i=MyCards.begin(); i != MyCards.end(); i++)
		result.push_back((*i).getValue());

	return result;
}

std::vector<std::pair<unsigned int, unsigned int>> getDifferentValues(const std::vector<Card> Cards) {
	std::vector<std::pair<unsigned int, unsigned int>> result (0);
	unsigned int value(Card::defaultValue);
	bool isPresent(false);

	if(!Cards.empty()) {
		for(std::vector<Card>::const_iterator i = Cards.begin(); i != Cards.end(); i++) {
			value = (*i).getValue();
			isPresent = false;

			for(std::vector<std::pair<unsigned int, unsigned int>>::iterator j = result.begin(); j != result.end(); j++) {
				if((*j).first == value && value != Card::defaultValue) {
					(*j).second ++;
					isPresent = true;
				}
			}
			if(!isPresent) result.push_back(std::pair<unsigned int, unsigned int> (value, 1));
		}
	}

	return result;
}

std::vector<std::pair<QChar, unsigned int>> getDifferentColors(const std::vector<Card> Cards) {
	std::vector<std::pair<QChar, unsigned int>> result (0);
	QChar color(Card::defaultColor);
	bool isPresent(false);

	if(!Cards.empty()) {
		for(std::vector<Card>::const_iterator i = Cards.begin(); i != Cards.end(); i++) {
			color = (*i).getColor();
			isPresent = false;

			for(std::vector<std::pair<QChar, unsigned int>>::iterator j = result.begin(); j != result.end(); j++) {
				if((*j).first == color && color != Card::defaultColor) {
					(*j).second ++;
					isPresent = true;
				}
			}
			if(!isPresent) result.push_back(std::pair<QChar, unsigned int> (color, 1));
		}
	}

	return result;
}

unsigned int lookForStraight(const std::vector<unsigned int> values) {
	unsigned int result(0);

	for(std::vector<unsigned int>::const_iterator i = values.begin(); i != values.end(); i++) {
		if(std::find(values.begin(), values.end(), (*i)+1) != values.end() &&
				std::find(values.begin(), values.end(), (*i)+2) != values.end() &&
				std::find(values.begin(), values.end(), (*i)+3) != values.end() &&
				std::find(values.begin(), values.end(), (*i)+4) != values.end() && result < (*i)+4)
			result = (*i)+4;
	}

	return result;
}

unsigned int getMaxValueOfColor(const QChar col, const std::vector<Card> myCards) {
	unsigned int result(0);
	unsigned int tmpVal(0);

	for (std::vector<Card>::const_iterator i = myCards.begin(); i != myCards.end(); i++) {
		tmpVal = (*i).getValue();

		if((*i).getColor() == col && tmpVal > result && tmpVal != Card::defaultValue)
			result = tmpVal;
	}

	return result;
}

void print_percentages_range() {
	Hand myHand;
	std::vector<std::pair<unsigned int, double>> combinVector;

	for(unsigned int i = Card::min_value; i <= Card::max_value; i++) {
		for(unsigned int j = Card::min_value; j <= Card::max_value; j++) {
			myHand.setCard(1, Card(i, Card::ClubsColor));
			myHand.setCard(2, Card(j, Card::ClubsColor));
			//combinVector.push_back(calculCombins(myHand));
		}
	}
}

std::vector<std::pair<unsigned int, double>> calculCombins(Hand h) {
	std::vector<std::pair<unsigned int, double>> result;

	for(unsigned int i = Combinaison::carteHaute; i <= Combinaison::quinteFlush; i++) {
		result.push_back(calculCombin(h, i));
	}

	return result;
}

std::pair<unsigned int, double> calculCombin(Hand h, unsigned int combin) {
	switch (combin) {
	case Combinaison::carteHaute:

	break;

	case Combinaison::paire:

	break;

	case Combinaison::doublePaire:

	break;

	case Combinaison::brelan:

	break;

	case Combinaison::quinte:

	break;

	case Combinaison::couleur:

	break;

	case Combinaison::full:

	break;

	case Combinaison::carre:

	break;

	case Combinaison::quinteFlush:

	break;

	default:
		Exception("functions").throwException("calculCombin(Hand h, unsigned int combin)", "combin not recognized");
	break;
	}
}

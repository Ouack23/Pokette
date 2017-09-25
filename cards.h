#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include "hand.h"
#include "combinaison.h"
#include "commoncards.h"
#include "exception.h"
#include "card.h"

class Cards
{
public:
	Cards();
	std::vector<Hand> getHands() const;
	CommonCards getCommonCards() const;
	std::vector<Card> getCommonCardsObjects() const;
	std::vector<Card> getAllCards() const;
	std::vector<Combinaison> getCombinaisons() const;
	Combinaison getCombinaisonOfHand(const unsigned int) const;
	std::vector<std::pair<Hand, Combinaison>> getAllHandsAndCombinaisons() const;
	std::vector<Card> getCardsFromHandAndCommonCards(const unsigned int) const;
	void setHand(const Hand, const unsigned int);
	void addHand(const Hand);
	void addCombinaison(const Combinaison);
	bool setCard(const unsigned int, const Card);
	bool setCommonCard(const unsigned int, const Card);
	void setCombinaisonOfHand(const Combinaison, const unsigned int);
	void updateCombinaisons();
	void updateCombinaison(const unsigned int i);
	QString getCombinaisonQString(const unsigned int) const;

private:
	std::vector<Hand> Hands;
	CommonCards MyCommonCards;
	std::vector<Combinaison> Combinaisons;
	Exception CardsException;
};

#endif // CARDS_H

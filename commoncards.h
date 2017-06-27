#ifndef COMMONCARDS_H
#define COMMONCARDS_H

#include "card.h"
#include "hand.h"
#include <vector>
#include "exception.h"
#include "combinaison.h"

class CommonCards
{
public:
	static const unsigned int PairSize = 2;
	static const unsigned int TripsSize = 3;
	static const unsigned int QuadsSize = 4;
	static const unsigned int FullSize = 5;

	CommonCards(std::vector<Card> = std::vector<Card>(5), Hand=Hand());
	~CommonCards();
	std::vector<Card> getFlop() const;
	Card getTurn() const;
	Card getRiver() const;
	Hand getHand() const;
	std::vector<Card> getCards() const;
	Card getCard(const unsigned int) const;
	void updateCombinaison();
	QString getCurrentCombinaisonQString() const;

	bool setCard(const unsigned int, Card);
	void setCombin(const Combinaison);
	bool isAlreadyOut(const Card) const;

private:
	std::vector<Card> TableCards;
	Hand HandCards;
	Combinaison currentCombin;
	Exception CommonCardsException;
};

#endif // COMMONCARDS_H

#ifndef HAND_H
#define HAND_H

#include <QString>
#include <vector>
#include "card.h"
#include "exception.h"

class Hand
{
public:
	Hand(Card=Card(), Card=Card());
	~Hand();
	Card getCard(const int) const;
	Card getOtherCard(const int) const;
	std::vector<Card> getCards() const;
	bool setCard(const int, const Card);
	void setHand(const Hand h);

private:
	std::vector<Card> Cards;
	Exception HandException;
};

#endif // HAND_H

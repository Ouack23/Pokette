#ifndef CARD_H
#define CARD_H

#include <QString>
#include <vector>
#include "exception.h"

class Card
{
public:
	static const unsigned int min_value, max_value, defaultValue;
	static const QChar defaultColor;

	static const unsigned int tenInt, jackInt, queenInt, kingInt, aceInt;
	static const QChar Ten, Jack, Queen, King, Ace;
	static const QString SpadesString, ClubsString, HeartsString, DiamondsString;
	static const QString JackString, QueenString, KingString, AceString;
	static const QChar SpadesColor, ClubsColor, HeartsColor, DiamondsColor;
	static const QChar Colors[4];

	Card(int=defaultValue, QChar=defaultColor);
	Card(Card const&);
	~Card();
	bool operator==(const Card &) const;
	bool operator!=(const Card &) const;
	unsigned int getValue() const;
	QChar getColor() const;
	QString getTitle() const;
	void setValue(const int);
	void setColor(QChar);
	void setCard(const QString);
	void setCard(const Card);
	Card getCard(const QString) const;
	QString getStyleSheet() const;
	QString getStringValue() const;

private:
	unsigned int value;
	QChar color;
	Exception CardException;
};

#endif // CARD_H

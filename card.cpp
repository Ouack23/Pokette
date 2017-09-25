#include "card.h"
#include <QString>
#include <QStringRef>
#include <iostream>
#include "exception.h"

const unsigned int Card::min_value(2);
const unsigned int Card::max_value(14);
const unsigned int Card::defaultValue(15);

const QChar Card::Ten('T');
const QChar Card::Jack('J');
const QChar Card::Queen('Q');
const QChar Card::King('K');
const QChar Card::Ace('A');

const unsigned int Card::tenInt(10);
const unsigned int Card::jackInt(11);
const unsigned int Card::queenInt(12);
const unsigned int Card::kingInt(13);
const unsigned int Card::aceInt(14);

const QString Card::JackString("jack");
const QString Card::QueenString("queen");
const QString Card::KingString("king");
const QString Card::AceString("ace");

const QString Card::SpadesString("spades");
const QString Card::ClubsString("clubs");
const QString Card::HeartsString("hearts");
const QString Card::DiamondsString("diamonds");

const QChar Card::SpadesColor('s');
const QChar Card::ClubsColor('c');
const QChar Card::HeartsColor('h');
const QChar Card::DiamondsColor('d');
const QChar Card::defaultColor('u');

const QChar Card::Colors[4] = {Card::SpadesColor, Card::ClubsColor, Card::HeartsColor, Card::DiamondsColor};

Card::Card(unsigned int val, QChar col):
	value(val),
	color(col),
	CardException(Exception("Card")) {

}

Card::Card(Card const& c):
	value(c.getValue()),
	color(c.getColor()),
	CardException(Exception("Card")) {

}

bool Card::operator==(const Card &c) const {
	return this->getColor() == c.getColor() &&
			this->getValue() == c.getValue();
}

bool Card::operator!=(const Card &c) const {
  return !(*this == c);
}

Card::~Card() {
}

unsigned int Card::getValue() const {
	return value;
}

QChar Card::getColor() const {
	return color;
}

void Card::setValue(const int val) {
	value = val;
}

void Card::setColor(const QChar col) {
	color = col;
}

bool Card::setCard(const Card c) {
	if(c.getValue() == Card::defaultValue || c.getColor() == Card::defaultColor) {
		CardException.throwException("setCard(const Card c)", "Something wrong, setting card to default values");
		return false;
	}

	setValue(c.getValue());
	setColor(c.getColor());

	if(getValue() != c.getValue() || getColor() != c.getColor()) {
		CardException.throwException("setCard(const Card c)", "Card hasn't been correctly set");
		return false;
	}

	return true;
}

bool Card::setCard(const QString title) {
	Card MyCard = getCard(title);
	return this->setCard(MyCard);
}

Card Card::getCard(const QString title) const {
	if(title.length() != 2) CardException.throwException("getCard(QString title)", "Invalid title : size != 2");

	QString::const_iterator i(title.begin());
	Card MyCard = Card();

	if((*i).isDigit()) MyCard.setValue(title.left(1).toInt());
	else if (*i == Ten) MyCard.setValue(tenInt);
	else if (*i == Jack) MyCard.setValue(jackInt);
	else if (*i == Queen) MyCard.setValue(queenInt);
	else if (*i == King) MyCard.setValue(kingInt);
	else if (*i == Ace) MyCard.setValue(aceInt);
	else CardException.throwException("getCard(QString title)", "Invalid title begin : not known value");
	i++;

	if (*i != SpadesColor && *i != ClubsColor && *i != HeartsColor && *i != DiamondsColor)
		CardException.throwException("getCard(QString title)", "Invalid title end : not know color");

	MyCard.setColor(*i);

	return MyCard;
}

QString Card::getStyleSheet() const {
	//background-image: url(:/10_of_diamonds.png);
	QString result = "_of_";

	if (getColor() == DiamondsColor) result.append(DiamondsString);
	else if (getColor() == SpadesColor) result.append(SpadesString);
	else if (getColor() == HeartsColor) result.append(HeartsString);
	else if (getColor() == ClubsColor) result.append(ClubsString);
	else CardException.throwException("getStyleSheet()", "Invalid color");

	unsigned int val = getValue();

	if (val <= tenInt) result.prepend(QString::number(val));

	else {
		switch(val) {
			case jackInt:
				result.prepend(JackString);
			break;
			case queenInt:
				result.prepend(QueenString);
			break;
			case kingInt:
				result.prepend(KingString);
			break;
			case aceInt:
				result.prepend(AceString);
			break;
			default:
				CardException.throwException("getStyleSheet()", "Invalid value");
			break;
		}
	}

	result.prepend(QString("background-image: url(:/"));
	result.append(QString(".png);"));

	return result;
}

QString Card::getStringValue() const {
	unsigned int val = getValue();
	QString result;

	if (val < tenInt) {
		result.append(QString::number(val));
	}
	else {
		switch(val) {
			case tenInt:
				result.append(Ten);
			break;
			case jackInt:
				result.append(Jack);
			break;
			case queenInt:
				result.append(Queen);
			break;
			case kingInt:
				result.append(King);
			break;
			case aceInt:
				result.append(Ace);
			break;
			case defaultValue:
			break;
			default:
				CardException.throwException("getStringValue()", "Invalid value");
			break;
		}
	}
	return result;
}

QString Card::getTitle() const {
	return getStringValue().append(getColor());
}

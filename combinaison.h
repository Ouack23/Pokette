#ifndef COMBINAISON_H
#define COMBINAISON_H

#include "exception.h"
#include <QString>

class Combinaison
{
public:
	static const unsigned int carteHaute = 0;
	static const unsigned int paire = 1;
	static const unsigned int doublePaire = 2;
	static const unsigned int brelan = 3;
	static const unsigned int quinte = 4;
	static const unsigned int couleur = 5;
	static const unsigned int full = 6;
	static const unsigned int carre = 7;
	static const unsigned int quinteFlush = 8;

	static const unsigned int defaultValue = 0;

	Combinaison(unsigned int = carteHaute, unsigned int = defaultValue, unsigned int = defaultValue);

	unsigned int getValue(const unsigned int) const;
	unsigned int getCombinValue() const;
	QString getValueString(const unsigned int) const;

	void setValue(const unsigned int, const unsigned int);
	void setComb(const unsigned int);
	void sortValues();
	void swapValues();

private:
	unsigned int combin;
	unsigned int value1;
	unsigned int value2;
	Exception CombinaisonException;
};

#endif // COMBINAISON_H

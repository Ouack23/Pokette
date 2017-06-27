#include "combinaison.h"
#include "card.h"
#include "exception.h"

Combinaison::Combinaison(unsigned int comb, unsigned int val1, unsigned int val2):
	combin(comb),
	value1(val1),
	value2(val2),
	CombinaisonException("Combinaison")
{

}

unsigned int Combinaison::getValue(const unsigned int n) const {
	switch(n) {
	case 1:
		return value1;
	break;

	case 2:
		return value2;
	break;

	default:
		CombinaisonException.throwException("getValue(unsigned int n)", "n is not 1 or 2");
		return 0;
	break;
	}
}

QString Combinaison::getValueString(const unsigned int n) const {
	switch(n) {
	case 1:
		return Card(value1).getStringValue();
	break;

	case 2:
		return Card(value2).getStringValue();
	break;

	default:
		CombinaisonException.throwException("getValueString(unsigned int n)", "n is not 1 or 2");
		return 0;
	break;
	}
}

void Combinaison::setValue(const unsigned int n, const unsigned int v) {
	if(v <= Card::max_value && v >= Card::min_value) {
		switch(n) {
		case 1:
			value1 = v;
		break;

		case 2:
			value2 = v;
		break;

		default:
			CombinaisonException.throwException("getValue(unsigned int n)", "n is not 1 or 2");
		break;
		}
	}
	else CombinaisonException.throwException("setValue(unsigned int, unsigned int)", "cannot set value !");
}

void Combinaison::sortValues() {
	if(value1 < value2) swapValues();
}

void Combinaison::swapValues() {
	unsigned int tmp = value1;
	value1 = value2;
	value2 = tmp;
}

unsigned int Combinaison::getCombinValue() const {
	return combin;
}

void Combinaison::setComb(const unsigned int c) {
	if(c <= quinteFlush)
		combin = c;
	else CombinaisonException.throwException("setComb(unsigned int)", "Cannot set this combination !");
}

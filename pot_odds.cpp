#include "pot_odds.h"
#include "exception.h"
#include <QString>

PotOdds::PotOdds():mise(0), pot(0), PotOddsException(Exception("PotOdds")) {

}

PotOdds::PotOdds(unsigned int miseValue, unsigned int potValue):
mise(miseValue),
pot(potValue)
{

}

PotOdds::~PotOdds() {

}

void PotOdds::setValues(const unsigned int miseVal, const unsigned int potVal) {
	mise = miseVal;
	pot = potVal;
}

double PotOdds::getPotOddsValue() const {
	double result = 1.0;
	if(mise+pot != 0) result = 100*(double)(mise)/(mise+pot);
	return result;
}

QString PotOdds::getPotOdds() const {
	return QString::number(getPotOddsValue());
}

QString PotOdds::getPotOdds2() const {
	QString result;
	if (pot != 0) result.append(QString::number((double)pot/mise));
	else PotOddsException.throwException("getPotOdds2()", "Division par 0 dans getPotOdds2()");
	result.append(":1");
	return result;
}

#ifndef POT_ODDS_H
#define POT_ODDS_H

#include <QString>
#include "exception.h"

class PotOdds
{
public:
	PotOdds();
	PotOdds(unsigned int, unsigned int);
	~PotOdds();
	double getPotOddsValue() const;
	QString getPotOdds() const;
	QString getPotOdds2() const;
	void setValues(const unsigned int miseVal, const unsigned int potVal);

private:
	unsigned int mise, pot;
	Exception PotOddsException;
};

#endif // POT_ODDS_H

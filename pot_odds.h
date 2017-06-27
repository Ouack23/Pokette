#ifndef POT_ODDS_H
#define POT_ODDS_H

#include <QString>
#include "exception.h"

class PotOdds
{
public:
	PotOdds();
	PotOdds(int, int);
	~PotOdds();
	double getPotOddsValue() const;
	QString getPotOdds() const;
	QString getPotOdds2() const;
	void setValues(const int miseVal, const int potVal);

private:
    int mise, pot;
	Exception PotOddsException;
};

#endif // POT_ODDS_H

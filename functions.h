#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "card.h"
#include "combinaison.h"
#include "hand.h"

std::vector<unsigned int> CardVectorToValuesVector(const std::vector<Card> MyCards);
std::vector<std::pair<unsigned int, unsigned int>> getDifferentValues(const std::vector<Card> Cards);
std::vector<std::pair<QChar, unsigned int>> getDifferentColors(const std::vector<Card> Cards);
Combinaison CombinCardVectorToCombin(const std::vector<Card>);
unsigned int getMaxValueOfColor(const QChar col, const std::vector<Card> myCards);
unsigned int lookForStraight(const std::vector<unsigned int> values);
std::pair<unsigned int, double> calculCombin(Hand h, unsigned int combin);
std::vector<std::pair<unsigned int, double>> calculCombins(Hand h);
void print_percentages_range();

#endif // FUNCTIONS_H

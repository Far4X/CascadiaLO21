#include "../Gametools/wildlifetoken.hpp"
#include "scoringstrategy.hpp"

class WildlifeScoringStrategy {
public:
	virtual void score(Cards card, Wildlife type) = 0;
};

#pragma once
#include "../GameTools/wildlifetoken.hpp"

enum Cards { A, B, C, D };

class ScoringStrategy {
public:
	virtual void computeScore(Cards card, Wildlife type) = 0;
};

#pragma once
#include "scoringstrategy.hpp"
#include "wildlifetoken.hpp" 

class Score {
	ScoringStrategy* m_card;  // aggregation
public:
	void obtainScore(Cards card, Wildlife type);
};
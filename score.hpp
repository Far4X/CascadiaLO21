#pragma once
#include "wildlifetoken.hpp" 

class Score {
	ScoringStrategy* m_mode;  // aggregation
public:
	void obtainScore(Wildlife type) {
		m_mode->computeScore(type)
	}
};
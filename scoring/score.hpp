#pragma once
#include "scoringstrategy.hpp"
#include "../GameTools/wildlifetoken.hpp"

class Score {
    ScoringStrategy* m_card = nullptr;  // aggregation
    ScoringStrategy* m_mode = nullptr;  // Bricolage pour compiler le projet

public:
	void obtainScore(Cards card, Wildlife type);
};

#pragma once
#include "../scoringstrategy.hpp"
#include "../wildlifescoringstrategy.hpp"

class ScoringCardD : public ScoringStrategy {
	WildlifeScoringStrategy* m_scorer;
public:
	void computeScore(Cards card, Wildlife type) override;
};
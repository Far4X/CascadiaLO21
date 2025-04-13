#pragma once
#include "../scoringstrategy.hpp"
#include "../wildlifescoringstrategy.hpp"

class ScoringCardA : public ScoringStrategy {
	WildlifeScoringStrategy* m_scorer;
public:
	void computeScore(Cards card, Wildlife type) override;
};
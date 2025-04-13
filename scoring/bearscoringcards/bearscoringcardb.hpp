#pragma once
#include "../wildlifescoringstrategy.hpp"

class BearScoringCardB : public WildlifeScoringStrategy {
public:
	void score(Cards card, Wildlife type) override;
};
#pragma once
#include "../wildlifescoringstrategy.hpp"

class BearScoringCardC : public WildlifeScoringStrategy {
public:
	void score(Cards card, Wildlife type) override;
};
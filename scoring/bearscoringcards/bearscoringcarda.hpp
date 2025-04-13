#pragma once
#include "../wildlifescoringstrategy.hpp"

class BearScoringCardA : public WildlifeScoringStrategy {
public:
	void score(Cards card, Wildlife type) override;
};
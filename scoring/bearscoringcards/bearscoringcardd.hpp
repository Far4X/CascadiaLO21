#pragma once
#include "../wildlifescoringstrategy.hpp"


class BearScoringCardD : public WildlifeScoringStrategy {
public:
	void score(Cards card, Wildlife type) override;
};

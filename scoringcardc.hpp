#pragma once
#include "scoringstrategy.hpp"

class ScoringCardC : public ScoringStrategy {
public:
	void computeScore(Wildlife type) override;
};
#pragma once
#include "scoringstrategy.hpp"

class ScoringCardB : public ScoringStrategy {
public:
	void computeScore(Wildlife type) override;
};
#pragma once
#include "scoringstrategy.hpp"

class ScoringCardA : public ScoringStrategy {
public:
	// DEFINE TEMPLATE ?

	void computeScore(Wildlife type) override;
};
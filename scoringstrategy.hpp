#pragma once
#include "wildlifetoken.hpp"

class ScoringStrategy {
public:
	virtual void computeScore(Wildlife type) = 0;
};
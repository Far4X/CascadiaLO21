#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class BearScoringCardC : public WildlifeScoringStrategy {
public:
    double computeScore(const PlayerBoard& board) const override;
};

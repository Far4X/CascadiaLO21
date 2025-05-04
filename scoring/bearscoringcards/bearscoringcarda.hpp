#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class BearScoringCardA : public WildlifeScoringStrategy {
public:
    double computeScore(const PlayerBoard& board) const override;
};

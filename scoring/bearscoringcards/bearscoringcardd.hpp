#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class BearScoringCardD : public WildlifeScoringStrategy {
public:
    double computeScore(const PlayerBoard& board) const override;
};

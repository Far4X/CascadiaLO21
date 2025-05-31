#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class SalmonScoringCardD : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

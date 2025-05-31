#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class SalmonScoringCardA : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

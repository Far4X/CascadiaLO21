#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class SalmonScoringCardC : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

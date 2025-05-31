#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class FoxScoringCardC : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

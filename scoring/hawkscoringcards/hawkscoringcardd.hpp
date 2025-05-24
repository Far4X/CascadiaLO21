#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"

class HawkScoringCardD : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

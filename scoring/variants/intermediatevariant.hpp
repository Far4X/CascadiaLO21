#pragma once
#include "scoring/scoringstrategies/wildlifescoringstrategy.hpp"


class IntermediateVariant : public WildlifeScoringStrategy {
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};

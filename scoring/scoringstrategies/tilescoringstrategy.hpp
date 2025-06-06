#pragma once

#include "scoring/scoringstrategy.hpp"

class TileScoringStrategy : ScoringStrategy {

public:
    TileScoringStrategy();
    std::vector<double> computeScore(const PlayerBoard& board) const override;
};


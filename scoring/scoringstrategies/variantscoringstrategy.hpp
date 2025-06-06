#pragma once

#include "scoring/scoringstrategy.hpp"

enum Variant { Family, Intermediate };

class VariantScoringStrategy : ScoringStrategy {
    Variant variant;
public:
    std::vector<double> computeScore(const PlayerBoard& board) const override;
    Variant getVariant() const { return variant; }
};


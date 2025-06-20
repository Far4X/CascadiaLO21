#pragma once

#include "scoring/scoringstrategy.hpp"

enum Variant { Family, Intermediate };

class VariantScoringStrategy : ScoringStrategy {
    Variant variant;
public:
    VariantScoringStrategy(Variant v);
    std::vector<double> computeScore(const PlayerBoard& board) const override;
    Variant getVariant() const { return variant; }
};


#pragma once

#include "scoring/score.hpp"

enum Cards { A, B, C, D };
class WildlifeScoringStrategy;

class ScoringStrategy {
public:
    virtual double computeScore(const PlayerBoard& board) const = 0;
    virtual ~ScoringStrategy() = default;
};

#pragma once

#include "Gametools/Abstract/playerboard.hpp"
#include <memory>

class ScoringStrategy;

class Score {
    std::unique_ptr<ScoringStrategy> m_card;  // aggregation


public:
    double obtainScore(const PlayerBoard& board) const;
    void setStrategy(std::unique_ptr<ScoringStrategy> card);
};

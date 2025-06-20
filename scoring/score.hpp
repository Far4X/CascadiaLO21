#pragma once

#include "../Gametools/Abstract/playerboard.hpp"
#include <memory>
#include <vector>

class ScoringStrategy;
class WildlifeScoringStrategy;
class TileScoringStrategy;
class VariantScoringStrategy;


class Score {
    static std::vector<std::string> m_animals;

    WildlifeScoringStrategy* m_active_card = nullptr; // aggregation
    std::vector<std::unique_ptr<WildlifeScoringStrategy>> m_scoring_cards;


public:
    Score();
    const std::vector<std::unique_ptr<WildlifeScoringStrategy>>& getScoringCards() const { return m_scoring_cards; }
    std::vector<double> obtainScore(const PlayerBoard& board) const;  // for tokens
    std::vector<double> obtainScore(const PlayerBoard& board, const TileScoringStrategy& strat) const;  // for tiles
    std::vector<double> obtainScore(const PlayerBoard& board, const VariantScoringStrategy& strat) const;  // for variants
    void setStrategy(size_t idx_card);  // for setting WildlifeScoringStrategy
    void configureCards(const std::string& cards);
};

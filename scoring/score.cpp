#include "score.hpp"
#include <iostream>
#include "scoring/scoringstrategy.hpp"

void Score::setStrategy(std::unique_ptr<ScoringStrategy> card) {
    m_card = std::move(card);
}


double Score::obtainScore(const PlayerBoard& board) const {
    if (m_card) {
        return m_card->computeScore(board);
    }
    else {
        std::cout<<"Strategy not set";
        return 0.0;
    }
}

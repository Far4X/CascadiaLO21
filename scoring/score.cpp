#include <iostream>
#include "score.hpp"
#include "scoringstrategies/wildlifescoringstrategy.hpp"
#include "scoringstrategies/tilescoringstrategy.hpp"
#include "scoring/scoreutils.hpp"


std::vector<std::string> Score::m_animals = {"Bear","Elk","Hawk","Fox","Salmon"};

Score::Score() : m_scoring_cards(5) {}

void Score::setStrategy(size_t idx_card) {
    m_active_card = m_scoring_cards.at(idx_card).get();
}


std::vector<double> Score::obtainScore(const PlayerBoard& board) const {
    if (m_active_card) {
        return m_active_card->computeScore(board);
    }
    else {
        std::cout<<"Strategy not set";
        return {0};
    }
}

std::vector<double> Score::obtainScore(const PlayerBoard& board, const TileScoringStrategy& strat) const {
    return strat.computeScore(board);
}

void Score::configureCards(const std::string& cards) {
    for (size_t i = 0; i < cards.size(); i++) {
        m_scoring_cards[i] = ScoreUtils::makeWildlifeStrategy(m_animals[i], cards[i]);
    }
}

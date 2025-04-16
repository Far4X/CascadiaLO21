#include "scoringcarda.hpp"

void ScoringCardA::computeScore(Cards card, Wildlife type) {
    m_scorer->score(card, type); //Bricolage, m_scorer->score(type) de base;
}

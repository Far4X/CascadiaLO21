#include "scoringcardc.hpp"

void ScoringCardC::computeScore(Cards card, Wildlife type) {
    m_scorer->score(card, type); //Bricolage, m_scorer->score(type) de base;
}

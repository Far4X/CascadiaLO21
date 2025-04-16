#include "scoringcardb.hpp"

void ScoringCardB::computeScore(Cards card, Wildlife type) {
    m_scorer->score(card, type); //Bricolage, m_scorer->score(type) de base;
}

#include "scoringcardb.hpp"

void ScoringCardB::computeScore(Cards card, Wildlife type) {
	m_scorer->score(type);
}
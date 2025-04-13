#include "scoringcarda.hpp"

void ScoringCardA::computeScore(Cards card, Wildlife type) {
	m_scorer->score(type);
}
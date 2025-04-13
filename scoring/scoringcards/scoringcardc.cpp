#include "scoringcardc.hpp"

void ScoringCardC::computeScore(Cards card, Wildlife type) {
	m_scorer->score(type);
}
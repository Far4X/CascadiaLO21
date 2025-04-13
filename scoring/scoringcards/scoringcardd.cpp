#include "scoringcardd.hpp"

void ScoringCardD::computeScore(Cards card, Wildlife type) {
	m_scorer->score(type);
}
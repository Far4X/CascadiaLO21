#include "score.hpp"

void Score::obtainScore(Cards card, Wildlife type) {
	m_mode->computeScore(card, type);
}
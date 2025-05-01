#include "score.hpp"

void Score::obtainScore(Cards card, Wildlife type) {
	m_mode->computeScore(card, type);
}

std::vector<std::vector<GameTile*>> Score::getAdjacentTiles(const Player& player) {
    //std::vector<std::vector<GameTile*>> gametiles = player.;
}

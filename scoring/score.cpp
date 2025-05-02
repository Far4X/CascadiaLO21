#include "score.hpp"

void Score::obtainScore(Cards card, Wildlife type) {
	m_mode->computeScore(card, type);
}


std::vector<std::vector<GameTile*>> Score::gatherAllTiles(const PlayerBoard& board, int size) {
    std::vector<std::vector<GameTile*>> tiles(size, std::vector<GameTile*>(size));
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tiles[y][x] = board.getTile(x, y);
        }
    }
    return tiles;
}

std::vector<std::vector<WildlifeToken*>> Score::gatherAllTokens(const PlayerBoard& board, int size) {
    std::vector<std::vector<WildlifeToken*>> tokens(size, std::vector<WildlifeToken*>(size));
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tokens[y][x] = board.getTile(x, y)->getToken();
        }
    }
    return tokens;
}

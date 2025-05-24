#include "scoreutils.hpp"

namespace ScoreUtils {

    TileGrid gatherAllTiles(const PlayerBoard& board, int size) {
        TileGrid tiles(size, std::vector<GameTile*>(size, nullptr));
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                tiles[y][x] = board.getTile(x, y);
            }
        }
        return tiles;
    }

    TokenGrid gatherAllTokens(const PlayerBoard& board, int size) {
        TokenGrid tokens(size, std::vector<WildlifeToken*>(size, nullptr));
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                GameTile* tile = board.getTile(x, y);
                if (tile != nullptr) {
                    tokens[y][x] = tile->getToken();
                }
            }
        }
        return tokens;
    }
}

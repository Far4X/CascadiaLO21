#include "tilescoringstrategy.hpp"
#include "scoring/scoreutils.hpp"

/*

TileScoringStrategy::TileScoringStrategy() {}

double TileScoringStrategy::computeScore(const PlayerBoard& board) const {
    ScoreUtils::TileGrid tiles = ScoreUtils::gatherAllTiles(board);
    double total_score = 0;
    for (auto biome : Animals) {
        auto groups = ScoreUtils::getAdjacentComponents(tiles, biome, MAX_SIZE);
        size_t max_size = 0;
        for (size_t i = 0; i < groups.size(); i++) {
            if (groups[i].size() > max_size) {
                max_size = groups[i].size();
            }
        }
        total_score += max_size;
    }
    return total_score;  // placeholder bien sûr
}

*/


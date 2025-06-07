#include "salmonscoringcardd.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_set>

std::vector<double> SalmonScoringCardD::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy salmon_d = ScoreUtils::makeWildlifePolicy(Salmon);
    auto salmons = ScoreUtils::getComponents(board, MAX_SIZE, salmon_d);

    int salmon_count = 0;
    int animal_count = 0;
    bool flag = true;
    for (size_t i = 0; i < salmons.size(); i++) {
        for (GameTile* salmon : salmons[i]) {
            if (board.getNbSameNeighbors(*salmon, Salmon) > 2) {
                flag = false;
            }
        }
        if (!flag) {
            flag = true;
            continue;  // on ignore ce groupe
        }
        std::unordered_set<GameTile*> seen;
        for (GameTile* salmon : salmons[i]) {
            salmon_count++;
            for (GameTile* neigh : board.getNeighborTiles(*salmon)) {
                if (neigh != nullptr && neigh->getToken() != nullptr && !neigh->matchesType(Salmon) && seen.insert(neigh).second) {
                    animal_count++;
                }
            }
        }
    }

    double final_score = salmon_count + animal_count;
    return {final_score};
}

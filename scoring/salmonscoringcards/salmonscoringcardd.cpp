#include "salmonscoringcardd.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_set>

std::vector<double> SalmonScoringCardD::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy salmon_a = ScoreUtils::makeNeighborPolicy(board, Salmon, 2, [](int count, int threshold){ return count <= threshold; });
    auto salmons = ScoreUtils::getComponents(board, MAX_SIZE, salmon_a);

    int salmon_count = 0;
    int animal_count = 0;
    for (const std::vector<GameTile*>& run : salmons) {
        std::unordered_set<GameTile*> seen;
        for (GameTile* salmon : run) {
            salmon_count++;
            for (GameTile* neigh : board.getNeighborTiles(*salmon)) {
                if (neigh->getToken() != nullptr && !neigh->matchesType(Salmon) && seen.insert(neigh).second) {
                    animal_count++;
                }
            }
        }
    }

    double final_score = salmon_count + animal_count;
    return {final_score};
}

#include "salmonscoringcardb.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> SalmonScoringCardB::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy salmon_b = ScoreUtils::makeNeighborPolicy(board, Salmon, 2, [](int count, int threshold){ return count <= threshold; });
    auto salmons = ScoreUtils::getComponents(board, MAX_SIZE, salmon_b);

    double final_score = 0;
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
        switch (salmons[i].size()) {
        case 0:
            break;
        case 1:
            final_score += 2;
            break;
        case 2:
            final_score += 4;
            break;
        case 3:
            final_score += 9;
            break;
        case 4:
            final_score += 11;
            break;
        default:
            final_score += 17;
        }
    }
    return {final_score};
}

#include "salmonscoringcardc.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> SalmonScoringCardC::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy salmon_c = ScoreUtils::makeNeighborPolicy(board, Salmon, 2, [](int count, int threshold){ return count <= threshold; });
    auto salmons = ScoreUtils::getComponents(board, MAX_SIZE, salmon_c);

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
            break;
        case 2:
            break;
        case 3:
            final_score += 10;
            break;
        case 4:
            final_score += 12;
            break;
        default:
            final_score += 15;
        }
    }
    return {final_score};
}

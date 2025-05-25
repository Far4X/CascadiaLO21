#include "salmonscoringcarda.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> SalmonScoringCardA::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy salmon_a = ScoreUtils::makeNeighborPolicy(board, Salmon, 2, [](int count, int threshold){ return count <= threshold; });
    auto salmons = ScoreUtils::getComponents(board, MAX_SIZE, salmon_a);

    double final_score = 0;
    for (size_t i = 0; i < salmons.size(); i++) {
        switch (salmons[i].size()) {
        case 0:
            break;
        case 1:
            final_score += 2;
            break;
        case 2:
            final_score += 5;
            break;
        case 3:
            final_score += 8;
            break;
        case 4:
            final_score += 12;
            break;
        case 5:
            final_score += 16;
            break;
        case 6:
            final_score += 20;
            break;
        default:
            final_score += 25;
        }
    }
    return {final_score};
}

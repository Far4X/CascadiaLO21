#include "elkscoringcardc.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> ElkScoringCardC::computeScore(const PlayerBoard& board) const {

    auto elks = ScoreUtils::getAdjacentComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Elk));

    double final_score = 0;
    for (size_t i = 0; i < elks.size(); i++) {
        switch (elks[i].size()) {
        case 0:
            break;
        case 1:
            final_score += 2;
            break;
        case 2:
            final_score += 4;
            break;
        case 3:
            final_score += 7;
            break;
        case 4:
            final_score += 10;
            break;
        case 5:
            final_score += 14;
            break;
        case 6:
            final_score += 18;
            break;
        case 7:
            final_score += 23;
            break;
        default:
            final_score += 28;
        }
	}
    return {final_score};
}

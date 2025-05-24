#include "hawkscoringcardc.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> HawkScoringCardC::computeScore(const PlayerBoard& board) const {

    auto hawks = ScoreUtils::getAdjacentComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Hawk));

    int cpt = 0;
    for (size_t i = 0; i < hawks.size(); i++) {
        if (hawks[i].size() == 2) {
            cpt += 1;
        }
    }
    double final_score = 0;
    switch (cpt) {
    case 0:
        break;
    case 1:
        final_score += 4;
        break;
    case 2:
        final_score += 11;
        break;
    case 3:
        final_score += 19;
        break;
    default:
        final_score += 27;
    }
    return {final_score};
}

#include "hawkscoringcardc.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> HawkScoringCardC::computeScore(const PlayerBoard& board) const {

    std::vector<std::pair<GameTile*, GameTile*>> los_pairs = ScoreUtils::getLinesOfSight(board, Hawk);
    double final_score = static_cast<int>(los_pairs.size()) * 3;
    return {final_score};
}

#include "hawkscoringcarda.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> HawkScoringCardA::computeScore(const PlayerBoard& board) const {

    auto hawks = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Hawk));

    int cpt = 0;
    for (size_t i = 0; i < hawks.size(); i++) {
        if (hawks[i].size() == 1) {
			cpt += 1;
		}
	}
    double final_score = 0;
	switch (cpt) {
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
            final_score += 11;
            break;
        case 5:
            final_score += 14;
            break;
        case 6:
            final_score += 18;
            break;
        case 7:
            final_score += 22;
            break;
		default:
            final_score += 26;
    }
    return {final_score};
}

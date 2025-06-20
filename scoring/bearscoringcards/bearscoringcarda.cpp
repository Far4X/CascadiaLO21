#include "bearscoringcarda.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> BearScoringCardA::computeScore(const PlayerBoard& board) const {

    auto bears = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Bear));

    int cpt = 0;
    for (size_t i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 2) {
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

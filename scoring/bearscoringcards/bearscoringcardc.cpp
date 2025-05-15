#include "bearscoringcardc.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> BearScoringCardC::computeScore(const PlayerBoard& board) const {

    auto tokens = ScoreUtils::gatherAllTokens(board);
    auto bears = ScoreUtils::getAdjacentComponents<WildlifeToken>(tokens, Bear, MAX_SIZE);

	int cpt_1 = 0;
	int cpt_2 = 0;
	int cpt_3 = 0;
    for (size_t i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 1) {
			cpt_1 += 1;
		}
		else if (bears[i].size() == 2) {
			cpt_2 += 1;
		}
		else if (bears[i].size() == 3) {
			cpt_3 += 1;
		}
	}
    double final_score = 2 * cpt_1 + 5 * cpt_2 + 8 * cpt_3;
	if (cpt_1 > 0 && cpt_2 > 0 && cpt_3 > 0) {
		final_score += 3;
	}
    return {final_score};
}

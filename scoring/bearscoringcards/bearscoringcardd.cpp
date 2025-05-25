#include "bearscoringcardd.hpp"
#include "scoring/scoreutils.hpp"


std::vector<double> BearScoringCardD::computeScore(const PlayerBoard& board) const {

    auto bears = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Bear));

	int cpt_2 = 0;
	int cpt_3 = 0;
	int cpt_4 = 0;
    for (size_t i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 2) {
			cpt_2 += 1;
		}
		else if (bears[i].size() == 3) {
			cpt_3 += 1;
		}
		else if (bears[i].size() == 4) {
			cpt_4 += 1;
		}
	}
    double final_score = 5 * cpt_2 + 8 * cpt_3 + 13 * cpt_4;
    return {final_score};
}

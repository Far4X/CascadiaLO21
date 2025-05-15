#include "bearscoringcardb.hpp"
#include "scoring/scoreutils.hpp"


std::vector<double> BearScoringCardB::computeScore(const PlayerBoard& board) const {

    auto tokens = ScoreUtils::gatherAllTokens(board);
    auto bears = ScoreUtils::getAdjacentComponents<WildlifeToken>(tokens, Bear, MAX_SIZE);

    double final_score = 0;
    for (size_t i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 3) {
			final_score += 10;
		}
	}
    return {final_score};
}

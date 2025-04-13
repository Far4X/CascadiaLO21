#include "bearscoringcardb.hpp"

void BearScoringCardB::score(Cards card, Wildlife type) {
	int final_score = 0;
	for (int i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 3) {
			final_score += 10;
		}
	}
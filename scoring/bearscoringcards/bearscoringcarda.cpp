#include "bearscoringcarda.hpp"

void BearScoringCardA::score(Cards card, Wildlife type) {
	int cpt = 0;
	for (int i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 2) {
			cpt += 1;
		}
	}
	int final_score = 0;
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
}
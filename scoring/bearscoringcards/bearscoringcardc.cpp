#include "bearscoringcardc.hpp"
#include "../../Gametools/Tiling/gametile.hpp"


void BearScoringCardC::score(Cards card, Wildlife type) {
	int cpt_1 = 0;
	int cpt_2 = 0;
	int cpt_3 = 0;
    std::vector<std::vector<GameTile*>> bears; //Brico pour compiler
	for (int i = 0; i < bears.size(); i++) {
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
	int final_score = 2 * cpt_1 + 5 * cpt_2 + 8 * cpt_3;
	if (cpt_1 > 0 && cpt_2 > 0 && cpt_3 > 0) {
		final_score += 3;
	}
}

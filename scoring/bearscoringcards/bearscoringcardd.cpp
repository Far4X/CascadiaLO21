#include "bearscoringcardd.hpp"
#include "../../Gametools/Tiling/gametile.hpp"


void BearScoringCardD::score(Cards card, Wildlife type) {
	int cpt_2 = 0;
	int cpt_3 = 0;
	int cpt_4 = 0;
    std::vector<std::vector<GameTile*>> bears; //Brico pour compiler

	for (int i = 0; i < bears.size(); i++) {
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
	int final_score = 5 * cpt_2 + 8 * cpt_3 + 13 * cpt_4;
}

#include "bearscoringcardb.hpp"
#include "../../Gametools/Tiling/gametile.hpp"


void BearScoringCardB::score(Cards card, Wildlife type) {
	int final_score = 0;
    std::vector<std::vector<GameTile*>> bears; //Brico pour compiler
	for (int i = 0; i < bears.size(); i++) {
		if (bears[i].size() == 3) {
			final_score += 10;
		}
	}
}

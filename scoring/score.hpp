#pragma once
#include "scoringstrategy.hpp"
#include <vector>
#include "../GameTools/wildlifetoken.hpp"
#include "Gametools/Tiling/gametile.hpp"
#include "GameActors/player.hpp"

class Score {
    ScoringStrategy* m_card = nullptr;  // aggregation
    ScoringStrategy* m_mode = nullptr;  // Bricolage pour compiler le projet

public:
	void obtainScore(Cards card, Wildlife type);
    std::vector<std::vector<GameTile*>> getAdjacentTiles(const Player&);
};

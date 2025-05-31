#include "tilescoringstrategy.hpp"
#include "scoring/scoreutils.hpp"
#include <vector>
#include <algorithm>

TileScoringStrategy::TileScoringStrategy() {}

std::vector<double> TileScoringStrategy::computeScore(const PlayerBoard& board) const {

    std::vector<double> largestPerBiome(Biomes.size(), 0.0);

    for (int biome = 0; biome < (int)Biomes.size(); biome++) {
        Biome filter = static_cast<Biome>(biome);

        auto groups = ScoreUtils::getAdjacentComponents(board, MAX_SIZE, ScoreUtils::makeBiomePolicy(board, filter));

        int best = 1;
        for (auto& cluster : groups) {
            best = std::max(best, (int)cluster.size());
        }

        largestPerBiome[biome] = static_cast<double>(best);
    }

    return largestPerBiome;
}

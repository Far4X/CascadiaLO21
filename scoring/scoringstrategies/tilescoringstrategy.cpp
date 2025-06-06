#include "tilescoringstrategy.hpp"
#include "scoring/scoreutils.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

TileScoringStrategy::TileScoringStrategy() {}

std::vector<double> TileScoringStrategy::computeScore(const PlayerBoard& board) const {

    std::vector<std::string> biomes = {"Forest", "Wetland", "River", "Mountain", "Prairie"};

    std::vector<double> largestPerBiome(Biomes.size(), 0.0);

    for (int biome = 0; biome < (int)Biomes.size(); biome++) {
        Biome filter = static_cast<Biome>(biome);
        std::cout << biomes[(int)biome] << " :" << std::endl;

        auto groups = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeBiomePolicy(board, filter));

        for (size_t i = 0; i < groups.size(); i++) {
            std::cout << "Component " << i << " size = " << groups[i].size() << std::endl;
        }

        int best = 1;
        for (auto& cluster : groups) {
            best = std::max(best, (int)cluster.size());
        }

        largestPerBiome[biome] = static_cast<double>(best);
    }

    return largestPerBiome;
}

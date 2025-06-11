#include "foxscoringcardd.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_map>
#include <unordered_set>

std::vector<double> FoxScoringCardD::computeScore(const PlayerBoard& board) const {

    ScoreUtils::AdjacencyPolicy fox_d = ScoreUtils::makeWildlifePolicy(Fox);
    auto foxes = ScoreUtils::getComponents(board, MAX_SIZE, fox_d);

    double final_score = 0;
    for (auto component : foxes) {
        if (component.size() != 2) {
            continue;
        }
        std::unordered_map<Wildlife, int> counts;
        std::unordered_set<GameTile*> neighbors;
        auto fox_1 = component[0];
        auto fox_2 = component[1];
        for (auto neigh : board.getNeighborTiles(*fox_1)) {
            if (neigh == nullptr || neigh == fox_2) {
                continue;
            }
            neighbors.insert(neigh);
        }
        for (auto neigh : board.getNeighborTiles(*fox_2)) {
            if (neigh == nullptr || neigh == fox_1) {
                continue;
            }
            neighbors.insert(neigh);
        }

        for (auto neigh : neighbors) {
            if (neigh != nullptr && neigh->getToken() != nullptr) {
                Wildlife animal = neigh->getToken()->getWildlifeType();
                if (animal == Fox) {
                    continue;
                }
                counts[animal]++;
            }
        }

        int count_pairs = 0;
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second == 2) {
                count_pairs++;
            }
        }
        switch (count_pairs) {
        case 0:
            break;
        case 1:
            final_score += 5;
            break;
        case 2:
            final_score += 7;
            break;
        case 3:
            final_score += 9;
            break;
        default:
            final_score += 11;
            break;
        }
    }
    return {final_score};
}

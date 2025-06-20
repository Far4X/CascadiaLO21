#include "foxscoringcardc.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_map>

std::vector<double> FoxScoringCardC::computeScore(const PlayerBoard& board) const {

    auto foxes = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeSingletonPolicy(Fox));

    double final_score = 0;
    for (auto component : foxes) {
        std::unordered_map<Wildlife, int> counts;
        auto fox = component[0];
        for (auto neigh : board.getNeighborTiles(*fox)) {
            if (neigh == nullptr || neigh->getToken() == nullptr) {
                continue;
            }
            Wildlife animal = neigh->getToken()->getWildlifeType();
            if (animal == Fox) {
                continue;
            }
            counts[animal]++;
        }
        int max_count = 0;
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            if (it->second > max_count) {
                max_count = it->second;
            }
        }
        switch (max_count) {
        case 0:
            break;
        case 1:
            final_score += 1;
            break;
        case 2:
            final_score += 2;
            break;
        case 3:
            final_score += 3;
            break;
        case 4:
            final_score += 4;
            break;
        case 5:
            final_score += 5;
            break;
        default:
            final_score += 6;
            break;
        }
    }
    return {final_score};
}

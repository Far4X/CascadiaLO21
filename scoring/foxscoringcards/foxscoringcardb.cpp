#include "foxscoringcardb.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_map>

std::vector<double> FoxScoringCardB::computeScore(const PlayerBoard& board) const {

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
                final_score += 3;
                break;
            case 2:
                final_score += 5;
                break;
            default:
                final_score += 7;
            break;
        }
    }
    return {final_score};
}

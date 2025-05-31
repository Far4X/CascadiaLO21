#include "foxscoringcarda.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_set>

std::vector<double> FoxScoringCardA::computeScore(const PlayerBoard& board) const {

    auto foxes = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeSingletonPolicy(Fox));

    double final_score = 0;
    for (auto component : foxes) {
        auto fox = component[0];
        std::unordered_set<Wildlife> active;
        std::unordered_set<Wildlife> invalid;
        for (auto neigh : board.getNeighborTiles(*fox)) {
            if (neigh == nullptr) {
                continue;
            }
            Wildlife animal = neigh->getToken()->getWildlifeType();
            if (active.count(animal)) {
                active.erase(animal);
                final_score--;
                invalid.insert(animal);
            }
            else if (!invalid.count(animal)) {
                active.insert(animal);
                final_score++;
            }
        }
    }
    return {final_score};
}

#include "foxscoringcarda.hpp"
#include "scoring/scoreutils.hpp"
#include <unordered_set>

std::vector<double> FoxScoringCardA::computeScore(const PlayerBoard& board) const {

    auto foxes = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeSingletonPolicy(Fox));

    double final_score = 0;
    for (auto component : foxes) {
        auto fox = component[0];
        std::unordered_set<Wildlife> active;
        for (auto neigh : board.getNeighborTiles(*fox)) {
            if (neigh != nullptr && neigh->getToken() != nullptr)
                active.insert(neigh->getToken()->getWildlifeType());
        }
        final_score += active.size();
    }
    return { final_score };
}

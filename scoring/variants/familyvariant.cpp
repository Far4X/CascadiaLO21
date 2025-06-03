#include "familyvariant.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> FamilyVariant::computeScore(const PlayerBoard& board) const {
    std::vector<double> final_score;
    std::vector<int> points_lookup = {0, 2, 5, 9};
    for (Wildlife animal : Animals) {
        auto groups = ScoreUtils::getComponents(board, animal, ScoreUtils::makeWildlifePolicy(animal));
        for (size_t i = 0; i < points_lookup.size(); i++) {
            if (groups[i].size() <= points_lookup.size()) {
                final_score.push_back(points_lookup[i]);
            }
            else {
                final_score.push_back(points_lookup.back());
            }
        }
    }
    return final_score;
}

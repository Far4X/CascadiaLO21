#include "variantscoringstrategy.hpp"
#include "scoring/scoreutils.hpp"

VariantScoringStrategy::VariantScoringStrategy(Variant v) : variant(v) {}

std::vector<double> VariantScoringStrategy::computeScore(const PlayerBoard& board) const {
    std::vector<double> final_score;
    std::vector<int> points_lookup;
    if (getVariant() == Family) {
        points_lookup = {0, 2, 5, 9};
    }
    else {
        points_lookup = {0, 0, 5, 8, 12};
    }
    for (Wildlife animal : Animals) {
        auto groups = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(animal));
        double total_score = 0;
        for (size_t i = 0; i < groups.size(); i++) {
            if (groups[i].size() < points_lookup.size()) {
                total_score += points_lookup[groups[i].size()];
            }
            else {
                total_score += points_lookup.back();
            }
        }
        final_score.push_back(total_score);
    }
    return final_score;
}

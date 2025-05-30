#include "hawkscoringcardd.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> HawkScoringCardD::computeScore(const PlayerBoard& board) const {

    auto hawks = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Hawk));
    std::vector<std::pair<GameTile*, GameTile*>> los_pairs = ScoreUtils::getLinesOfSight(board, Hawk);

    ScoreUtils::TileGrid candidates;
    std::vector<int> points;
    std::vector<int> points_lookup = { 4, 7, 9 };

    for (const auto& pair : los_pairs) {
        GameTile* a = pair.first;
        GameTile* b = pair.second;
        int n = ScoreUtils::countUniqueTokensBetween(board, a, b, Wildlife::Hawk);

        candidates.push_back({ a, b });
        int pts;
        if (n < static_cast<int>(points_lookup.size())) {
            pts = points_lookup[n];
        }
        else {
            pts = points_lookup.back();
        }
        points.push_back(pts);
    }

    int final_score = 0;
    std::unordered_set<GameTile*> used;

    ScoreUtils::dfs(0, 0, final_score, points, candidates, used);

    return {(double)final_score};
}

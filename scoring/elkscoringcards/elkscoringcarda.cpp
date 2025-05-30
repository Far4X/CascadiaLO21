#include "elkscoringcarda.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> ElkScoringCardA::computeScore(const PlayerBoard& board) const {

    int final_score = 0;
    ScoreUtils::TileGrid candidates;
    std::vector<int> points;
    std::vector<int> points_lookup = { 0, 2, 5, 9, 13 };
    ScoreUtils::getLineFormations(board, MAX_SIZE, Elk, candidates, points, points_lookup);
    std::unordered_set<GameTile*> used;

    ScoreUtils::dfs(0, 0, final_score, points, candidates, used);

    return {(double)final_score};
}

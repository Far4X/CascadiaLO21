#include "hawkscoringcardb.hpp"
#include "scoring/scoreutils.hpp"

std::vector<double> HawkScoringCardB::computeScore(const PlayerBoard& board) const {

    auto hawks = ScoreUtils::getComponents(board, MAX_SIZE, ScoreUtils::makeWildlifePolicy(Hawk));

    std::unordered_set<GameTile*> isolated;

    for (const std::vector<GameTile*>& component : hawks) {
        if (component.size() == 1) {
            isolated.insert(component[0]);
        }
    }

    std::vector<std::pair<GameTile*, GameTile*>> los_pairs = ScoreUtils::getLinesOfSight(board, Hawk);

    std::unordered_set<GameTile*> has_los;
    for (auto pair : los_pairs) {
        has_los.insert(pair.first);
        has_los.insert(pair.second);
    }

    int cpt = 0;

    for (GameTile* hawk : isolated) {
        if (has_los.count(hawk)) {
            cpt++;
        }
    }

    double final_score = 0;
    switch (cpt) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        final_score += 5;
        break;
    case 3:
        final_score += 9;
        break;
    case 4:
        final_score += 12;
        break;
    case 5:
        final_score += 16;
        break;
    case 6:
        final_score += 20;
        break;
    case 7:
        final_score += 24;
        break;
    default:
        final_score += 28;
        break;
    }
    return {final_score};
}

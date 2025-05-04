#ifndef TILESCORINGSTRATEGY_H
#define TILESCORINGSTRATEGY_H

#include "scoring/scoringstrategy.hpp"

class TileScoringStrategy : ScoringStrategy {
public:
    TileScoringStrategy();
    double computeScore(const PlayerBoard& board) const override {
        return 123.0;  // placeholder bien sûr
    }
};

#endif // TILESCORINGSTRATEGY_H

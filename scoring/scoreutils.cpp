#include "scoreutils.hpp"
#include "bearscoringcards/bearscoringcarda.hpp"
#include "bearscoringcards/bearscoringcardb.hpp"
#include "bearscoringcards/bearscoringcardc.hpp"
#include "bearscoringcards/bearscoringcardd.hpp"

namespace ScoreUtils {
    std::unique_ptr<WildlifeScoringStrategy> makeWildlifeStrategy(const std::string& animal, char code) {
        if (animal == "Bear") {
            switch(code) {
                case 'A' :
                    return std::make_unique<BearScoringCardA>();
                case 'B' :
                    return std::make_unique<BearScoringCardB>();
                case 'C' :
                    return std::make_unique<BearScoringCardC>();
                case 'D' :
                    return std::make_unique<BearScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else if (animal == "Elk") {
            switch(code) {
                case 'A' :
                    return std::make_unique<BearScoringCardA>();
                case 'B' :
                    return std::make_unique<BearScoringCardB>();
                case 'C' :
                    return std::make_unique<BearScoringCardC>();
                case 'D' :
                    return std::make_unique<BearScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else if (animal == "Hawk") {
            switch(code) {
                case 'A' :
                    return std::make_unique<BearScoringCardA>();
                case 'B' :
                    return std::make_unique<BearScoringCardB>();
                case 'C' :
                    return std::make_unique<BearScoringCardC>();
                case 'D' :
                    return std::make_unique<BearScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else if (animal == "Fox") {
            switch(code) {
                case 'A' :
                    return std::make_unique<BearScoringCardA>();
                case 'B' :
                    return std::make_unique<BearScoringCardB>();
                case 'C' :
                    return std::make_unique<BearScoringCardC>();
                case 'D' :
                    return std::make_unique<BearScoringCardD>();
                    default:
                throw "invalid code";
            }
        }
        else if (animal == "Salmon") {
            switch(code) {
                case 'A' :
                    return std::make_unique<BearScoringCardA>();
                case 'B' :
                    return std::make_unique<BearScoringCardB>();
                case 'C' :
                    return std::make_unique<BearScoringCardC>();
                case 'D' :
                    return std::make_unique<BearScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else {
            throw "invalid animal";
        }
    }
}

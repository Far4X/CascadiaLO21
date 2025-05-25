#include "scoreutils.hpp"
#include "bearscoringcards/bearscoringcarda.hpp"
#include "bearscoringcards/bearscoringcardb.hpp"
#include "bearscoringcards/bearscoringcardc.hpp"
#include "bearscoringcards/bearscoringcardd.hpp"
#include <cassert>

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

    TileGrid gatherAllTiles(const PlayerBoard& board, int size) {
        TileGrid tiles(size, std::vector<GameTile*>(size, nullptr));
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                tiles[y][x] = board.getTile(x, y);
            }
        }
        return tiles;
    }

    // Création de l'UnionFind avec les tuiles élaguées
    UnionFind buildUnionFind(const PlayerBoard& board, int size, const AdjacencyPolicy& policy, TileGrid& tiles) {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                GameTile* tile = board.getTile(x, y);
                if (tile != nullptr && policy.shouldKeep(tile)) {
                    tiles[y][x] = tile;
                }
                else {
                    tiles[y][x] = nullptr;
                }
            }
        }

        size_t n = static_cast<size_t>(size) * size;
        UnionFind uf(n);

        // élaguation de tuiles
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                GameTile* curr = tiles[y][x];
                if (curr == nullptr) {
                    continue;
                }
                int curr_id = curr->getId();

                auto neighs = board.getNeighborTiles(*curr);
                for (GameTile* neigh : neighs) {
                    if (neigh == nullptr || !policy.shouldKeep(neigh))
                        continue;
                    if (policy.shouldUnite(curr, neigh)) {
                        uf.unite(curr_id, neigh->getId());
                    }
                }
            }
        }

        return uf;
    }

    // Groupage des tuiles par parent
    TileGrid buildBuckets(const TileGrid& tiles, UnionFind uf) {
        size_t size = tiles.size();
        size_t n = size * size;
        TileGrid buckets(n);

        for (size_t y = 0; y < size; y++) {
            for (size_t x = 0; x < size; x++) {
                GameTile* tile = tiles[y][x];
                if (tile == nullptr) {
                    continue;
                }
                int root = uf.find(tile->getId());
                buckets[root].push_back(tile);
            }
        }

        return buckets;
    }

    // Extraction des groupes non-vides
    TileGrid extractGroups(TileGrid buckets) {
        TileGrid groups;
        for (auto& b : buckets) {
            if (!b.empty())
                groups.push_back(std::move(b));
        }
        return groups;
    }

    // Fonction principale
    TileGrid getComponents(const PlayerBoard& board, int size, const AdjacencyPolicy& policy) {
        TileGrid tiles(size, std::vector<GameTile*>(size, nullptr));
        UnionFind uf = buildUnionFind(board, size, policy, tiles);
        TileGrid buckets = buildBuckets(tiles, uf);
        return extractGroups(std::move(buckets));
    }


    // Mode 1: Adjacence - biomes
    AdjacencyPolicy makeBiomePolicy(const PlayerBoard& board, Biome filter) {
        return AdjacencyPolicy(
            // si la tuile courante possède le biome recherché du côté courant
            [filter](GameTile* tile) {
                for (int side = 0; side < 6; side++)
                    if (tile->getBiome(side) == filter)
                        return true;
                return false;
            },
            // si le voisin possède le même biome du côté opposé
            [&board, filter](GameTile* curr, GameTile* /*neigh*/) {
                for (int side = 0; side < 6; side++) {
                    if (curr->getBiome(side) != filter)
                        continue;
                    Direction d = static_cast<Direction>(side);
                    GameTile* neigh = board.getNeighborTile(*curr, d);
                    if (neigh == nullptr) {
                        continue;
                    }
                    int opp_side = (side + 3) % 6;
                    if (neigh->getBiome(opp_side) == filter) {
                        return true;
                    }
                }
                return false;
            }
        );
    }

    // Mode 2: Adjacence - tokens
    AdjacencyPolicy makeWildlifePolicy(Wildlife filter) {
        return AdjacencyPolicy(
            [filter](GameTile* tile) {
                return tile->matchesType(filter);
            },
            [filter](GameTile* /*curr*/, GameTile* neigh) {  // on utilise pas curr mais on garde son spot pour respecter le protoype
                return neigh->matchesType(filter);
            }
        );
    }

    // Mode 2: Singletons - tokens
    AdjacencyPolicy makeSingletonPolicy(Wildlife filter) {
        return AdjacencyPolicy(
            [filter](GameTile* tile) {
                return tile->matchesType(filter);
            },
            [](GameTile* /*curr*/, GameTile* /*neigh*/) {
                return false;
            }
            );
    }

    // Mode 3: Adjacence - nombre de voisins similaires
    AdjacencyPolicy makeNeighborPolicy(const PlayerBoard& board, Wildlife filter, int threshold, CompareFunction cmp) {
        return AdjacencyPolicy(
            [&board, filter, threshold, cmp](GameTile* tile) {
                return tile->matchesType(filter) && cmp(board.getNbSameNeighbors(*tile, filter), threshold);
            },
            [](GameTile* /*curr*/, GameTile* /*neigh*/) {  // pareil ici mais pour les deux
                return true;  // ici le comportement est déjà géré par la fonction shouldKeep donc c'est bidon
            }
        );
    }
    /*
    // Mode 3: Adjacence - nombre de voisins
    AdjacencyPolicy makeNeighborPolicy(const PlayerBoard& board, Wildlife filter, int threshold, CompareFunction cmp) {
        return AdjacencyPolicy(
            [&board, filter, threshold, cmp](GameTile* tile) {
                return cmp(board.getNbNeighbors(*tile), threshold);
            },
            [](GameTile*, GameTile*) {  // pareil ici mais pour les deux
                return true;  // ici le comportement est déjà géré par la fonction shouldKeep donc c'est bidon
            }
        );
    }
    */

    // Combiner des modes
    AdjacencyPolicy combinePolicies(const AdjacencyPolicy& a, const AdjacencyPolicy& b) {
        return AdjacencyPolicy(
            // ne conserve que si les deux policies gardent
            [a,b](GameTile* t){ return a.shouldKeep(t) && b.shouldKeep(t); },
            // unit deux tiles si les deux policies unissent
            [a,b](GameTile* curr, GameTile* nb){
                return a.shouldUnite(curr, nb) && b.shouldUnite(curr, nb);
            }
        );
    }

    std::vector<GameTile*> flatten(const std::vector<std::vector<GameTile*>>& groups) {
        std::vector<GameTile*> flat;
        for (const auto& group : groups) {
            flat.insert(flat.end(), group.begin(), group.end());
        }
        return flat;
    }

    GameTile* findTile(const std::vector<GameTile*>& tiles, int q, int r) {
        for (auto tile : tiles) {
            if (tile == nullptr) {
                continue;
            }
            if (*tile == HexCell(q, r))
                return tile;
        }
        return nullptr;
    }

    std::vector<std::pair<GameTile*,GameTile*>> getLinesOfSight(const PlayerBoard& board, Wildlife filter) {
        auto groups = getComponents(board, MAX_SIZE, makeWildlifePolicy(filter));
        auto tiles = flatten(groups);  // juste pour avoir un vecteur simple au lieu d'un vecteur de vecteurs à un élément à l'intérieur
        std::vector<std::pair<GameTile*, GameTile*>> lines;  // lines of sight (paire tuile source et tuile destination)
        for (auto src : tiles) {
            int q0 = src->getQ();
            int r0 = src->getR();
            for (const HexCell& dir : HexCell::directions) {
                int q = q0;
                int r = r0;
                while (true) {
                    // on avance d'un pas dans la direction dir
                    q += dir.getQ();
                    r += dir.getR();

                    GameTile* hit = findTile(tiles, q, r);  // tuile atteinte
                    if (hit == nullptr) {
                        break;
                    }
                    bool seen = false;
                    for (const auto& pair : lines) {
                        if ((pair.first == src && pair.second == hit) || (pair.first == hit && pair.second == src)) {  // si on a déjà vu la paire
                            seen = true;
                            break;
                        }
                    }
                    if (!seen) {
                        lines.emplace_back(src, hit);
                    }
                    break;  // on sort pour explorer une autre direction
                }
            }
        }
        return lines;
    }
}

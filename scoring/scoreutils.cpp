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
    TileGrid getAdjacentComponents(const PlayerBoard& board, int size, const AdjacencyPolicy& policy) {
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

    // Mode 3: Adjacence - nombre de voisins
    AdjacencyPolicy makeNeighborPolicy(const PlayerBoard& board, int threshold, CompareFunction cmp) {
        return AdjacencyPolicy(
            [&board, threshold, cmp](GameTile* tile) {
                return cmp(board.getNbNeighbors(*tile), threshold);
            },
            [](GameTile* /*curr*/, GameTile* /*neigh*/) {  // pareil ici mais pour les deux
                return true;  // ici le comportement est déjà géré par la fonction shouldKeep donc c'est bidon
            }
        );
    }
}

#pragma once

#include "Gametools/Tiling/gametile.hpp"
#include "Gametools/Abstract/playerboard.hpp"
#include "scoring/scoringstrategy.hpp"
#include <vector>
#include <memory>
#include <functional>


namespace ScoreUtils {
    using TileGrid  = std::vector<std::vector<GameTile*>>;
    using CompareFunction= std::function<bool(int,int)>;
    std::unique_ptr<WildlifeScoringStrategy> makeWildlifeStrategy(const std::string& wildlife, char card);
    TileGrid gatherAllTiles(const PlayerBoard& board, int size = MAX_SIZE);
    TileGrid pruneTiles(const PlayerBoard& board, std::vector<GameTile*> tiles, std::function<bool(int,int)> cmp, int threshold);


    class UnionFind {  // c'est une structure de données super utile que j'ai trouvée, elle permet de réunir des set de manière efficace ce dont j'ai besoin pour la recherche de groupes adjacents
        std::vector<int> parent;
        std::vector<int> rank;
    public:
        explicit UnionFind(int n) : parent(n), rank(n, 0) {
            for(int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) {
                return;
            }
            if (rank[a] < rank[b]) {
                parent[a] = b;
            }
            else if (rank[b] < rank [a]) {
                parent[b] = a;
            }
            else {
                parent[b] = a;
                rank[a] += 1;
            }
        }

        bool areConnected(int a, int b) {
            return find(a) == find(b);
        }
    };

#include <vector>
#include <functional>

    using TileGrid = std::vector<std::vector<GameTile*>>;

    // struct représentant les conditions pour choisir une tuile
    using KeepTile = std::function<bool(GameTile*)>;
    using UniteTile = std::function<bool(GameTile*, GameTile*)>;
    struct AdjacencyPolicy {
        KeepTile shouldKeep;
        UniteTile shouldUnite;
        AdjacencyPolicy(KeepTile k, UniteTile u) : shouldKeep(std::move(k)), shouldUnite(std::move(u)) {}
    };
    UnionFind buildUnionFind(const PlayerBoard& board, int size, const AdjacencyPolicy& policy, TileGrid& tiles);
    TileGrid buildBuckets(const TileGrid& tiles, UnionFind uf);
    TileGrid extractGroups(TileGrid buckets);
    TileGrid getAdjacentComponents(const PlayerBoard& board, int size, const AdjacencyPolicy& policy);
    AdjacencyPolicy makeBiomePolicy(const PlayerBoard& board, Biome filter);
    AdjacencyPolicy makeWildlifePolicy(Wildlife filter);
    AdjacencyPolicy makeNeighborPolicy(const PlayerBoard& board, int threshold, CompareFunction cmp);
    // TileGrid getLongestRun(const PlayerBoard& board, std::vector<std::vector<GameTile*>> tiles);
}


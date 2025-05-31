#pragma once

#include "Gametools/Tiling/gametile.hpp"
#include "Gametools/Abstract/playerboard.hpp"
#include "scoring/scoringstrategy.hpp"
#include <vector>
#include <memory>
#include <functional>
#include <unordered_set>


namespace ScoreUtils {
    using TileGrid  = std::vector<std::vector<GameTile*>>;
    using TokenGrid = std::vector<std::vector<WildlifeToken*>>;
    std::unique_ptr<WildlifeScoringStrategy> makeWildlifeStrategy(const std::string& wildlife, char card);
    std::vector<std::vector<GameTile*>> gatherAllTiles(const PlayerBoard& board, int size = MAX_SIZE);


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

    // struct représentant les conditions pour choisir une tuile
    using KeepTile = std::function<bool(GameTile*)>;
    using UniteTile = std::function<bool(GameTile*, GameTile*)>;
    using CompareFunction = std::function<bool(int,int)>
    struct AdjacencyPolicy {
        KeepTile shouldKeep;
        UniteTile shouldUnite;
        AdjacencyPolicy(KeepTile k, UniteTile u) : shouldKeep(std::move(k)), shouldUnite(std::move(u)) {}
    };
    UnionFind buildUnionFind(const PlayerBoard& board, int size, const AdjacencyPolicy& policy, TileGrid& tiles);
    TileGrid buildBuckets(const TileGrid& tiles, UnionFind uf);
    TileGrid extractGroups(TileGrid buckets);
    TileGrid getComponents(const PlayerBoard& board, int size, const AdjacencyPolicy& policy);
    AdjacencyPolicy makeBiomePolicy(const PlayerBoard& board, Biome filter);
    AdjacencyPolicy makeWildlifePolicy(Wildlife filter);
    AdjacencyPolicy makeNeighborPolicy(const PlayerBoard& board, Wildlife filter, int threshold, CompareFunction cmp);
    AdjacencyPolicy makeSingletonPolicy(Wildlife filter);
    AdjacencyPolicy combinePolicies(const AdjacencyPolicy& a, const AdjacencyPolicy& b);
    std::vector<GameTile*> flatten(const std::vector<std::vector<GameTile*>>& groups);
    GameTile* findTile(const std::vector<GameTile*>& tiles, int q, int r);
    void getLineFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup);
    void getRingFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup);
    void getShapeFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup);
    void dfs(int idx, int curr_score, int& best_score, const std::vector<int>& points, const TileGrid& candidates, std::unordered_set<GameTile*>& used);
    struct Match {
        int matchId;
        std::vector<GameTile*> tiles;
    };
    std::vector<std::pair<GameTile*,GameTile*>> getLinesOfSight(const PlayerBoard& board, Wildlife filter);
    std::vector<std::vector<HexCell>> getOrientations(const std::vector<HexCell>& shape);
    std::vector<std::vector<HexCell>> getAllTemplates(const std::vector<std::vector<HexCell>>& shapes);
    int countUniqueTokensBetween(const PlayerBoard& board, GameTile* a, GameTile* b, Wildlife filter);
}


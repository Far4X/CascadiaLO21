#pragma once

#include "Gametools/Tiling/gametile.hpp"
#include "Gametools/Abstract/playerboard.hpp"
#include "scoring/scoringstrategy.hpp"
#include <vector>
#include <memory>
<<<<<<< Updated upstream
=======
#include <functional>
#include <unordered_set>
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes


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

<<<<<<< Updated upstream
    template <typename Type>
    std::vector<std::vector<GameTile*>> getAdjacentComponents(const PlayerBoard& board, int mode, Type filter, int size) {
        /* idée : pour chaque tuile, on récupère les voisins, ensuite pour chaque voisin, on va comparer selon le critère d'adjacence
        * qui nous intéresse. Enfin, on applique l'algo UnionFind.
        */
        TileGrid tiles(size, std::vector<GameTile*>(size, nullptr));
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                tiles[y][x] = board.getTile(x, y);
            }
        }
        size_t n = size * size;
        UnionFind uf(n);
        // boucle principale sur tuiles
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                GameTile* curr_tile = tiles[y][x];
                if (curr_tile == nullptr || !curr_tile->matchesType(filter)) {
                    continue;
                }
                int curr_id = curr_tile->getId();
                // traitement voisins
                if (mode == 1) {
                    // mode biome
                    for (int side = 0; side < 6; side++) {
                        if (curr_tile->getBiome(side) != filter) {
                            continue;
                        }
                        Direction d = static_cast<Direction>(side);
                        GameTile* neigh_tile = board.getNeighborTile(*curr_tile, d);
                        if (neigh_tile == nullptr) {
                            continue;
                        }
                        int opp_side = (side + 3) % 6;
                        if (neigh_tile->getBiome(opp_side) != filter) {
                            continue;
                        }
                        int neigh_id = neigh_tile->getId();
                        if (neigh_id > curr_id) {
                            uf.unite(neigh_id, curr_id);
                        }
                    }
                }
                else if (mode == 2){
                    // mode wildlife
                    auto neighs = board.getNeighborTiles(*curr_tile);
                    for (size_t i = 0; i < neighs.size(); i++) {
                        GameTile* neigh_tile = neighs[i];
                        if (neigh_tile == nullptr || !neigh_tile->matchesType(filter)) {
                            continue;
                        }
                        int neigh_id = neigh_tile->getId();
                        uf.unite(curr_id, neigh_id);
                    }
                }
                else {
                    throw "Mode invalide";
                }
            }
        }
        // maintenant, on va regrouper les Component par parent (représentatif c.f. vidéo que j'ai envoyé sur Union Find)
        std::vector<std::vector<GameTile*>> buckets(n);
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                GameTile* tile = tiles[y][x];
                if (!tile || !tile->matchesType(filter))  // redondant mais au cas où
                    continue;
                int root = uf.find(tile->getId());
                buckets[root].push_back(tile);
            }
        }
        // enfin, on va créer les vrais groupes, cette fois ci en supprimant aussi les indices ou c'est vide
        std::vector<std::vector<GameTile*>> groups;
        for (size_t id = 0; id < n; id++) {
            if (!buckets[id].empty())
                groups.push_back(std::move(buckets[id]));
        }
        return groups;
    }
=======
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
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}


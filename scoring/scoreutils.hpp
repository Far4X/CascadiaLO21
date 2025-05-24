#pragma once

#include "Gametools/Tiling/gametile.hpp"
#include "Gametools/Abstract/playerboard.hpp"
#include <vector>

namespace ScoreUtils {
    using TileGrid  = std::vector<std::vector<GameTile*>>;
    using TokenGrid = std::vector<std::vector<WildlifeToken*>>;

    std::vector<std::vector<GameTile*>> gatherAllTiles(const PlayerBoard& board, int size = MAX_SIZE);
    std::vector<std::vector<WildlifeToken*>> gatherAllTokens(const PlayerBoard& board, int size = MAX_SIZE);

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

    template <typename Component, typename Type>
    std::vector<std::vector<Component*>> getAdjacentComponents(const std::vector<std::vector<Component*>>& components, Type filter, int size) {
        /* idée : on retrouve la HexCell associée à la GameTile ou (de manière plus importante) du WildlifeToken, puis on récupère les voisins de cette cellule, ensuite pour chaque voisin,
    * on regarde ses coordonnées Offset (s'ils existent) dans le tableau 2D et finalement on récupère la GameTile ou WildlifeToken à cet endroit pour effectuer le Union Find
    */
        size_t n = size * size;
        UnionFind uf(n);
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                Component* component = components[y][x];
                if (component == nullptr || !component->matchesType(filter)) {
                    continue;
                }
                PlayerBoard::Offset component_off(x, y);
                HexCell component_hex = PlayerBoard::offsetToAxial(component_off);  // on retouve la gametile associée au Component
                int id = y * size + x;
                // traitement voisins
                auto neighs = component_hex.getNeighbors();
                for (size_t i = 0; i < neighs.size(); i++) {
                    HexCell neighHex = neighs[i];
                    PlayerBoard::Offset off = PlayerBoard::axialToOffset(neighHex);  // on convertit en Offset pour voir à quelle case dans le tableau 2D le voisin correspond
                    int off_x = off.getCol();
                    int off_y = off.getRow();
                    if (off_x < 0 || off_x >= size || off_y < 0 || off_y >= size)  // vérification que les coordonnées du voisin sont valides
                        continue;
                    int nid = off_y * size + off_x;
                    Component* n = components[off_y][off_x];  // le voisin du Component courant c
                    if (n == nullptr || !n->matchesType(filter)) {
                        continue;
                    }
                    uf.unite(id, nid);
                }
            }
        }
        // maintenant, on va regrouper les Component par parent (représentatif c.f. vidéo que j'ai envoyé sur Union Find)
        std::vector<std::vector<Component*>> buckets(n);
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                Component* c = components[y][x];
                if (!c || !c->matchesType(filter))  // redondant mais au cas où
                    continue;
                int root = uf.find(y * size + x);
                buckets[root].push_back(c);
            }
        }
        // enfin, on va créer les vrais groupes, cette fois ci en supprimant aussi les indices ou c'est vide
        std::vector<std::vector<Component*>> groups;
        for (size_t id = 0; id < n; id++) {
            if (!buckets[id].empty())
                groups.push_back(std::move(buckets[id]));
        }
        return groups;
    }
}


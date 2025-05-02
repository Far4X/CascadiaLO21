#pragma once
#include "scoringstrategy.hpp"
#include <vector>
#include "../GameTools/wildlifetoken.hpp"
#include "Gametools/Tiling/gametile.hpp"
#include "GameActors/player.hpp"
#include "Gametools/Abstract/playerboard.hpp"

class Score {
    ScoringStrategy* m_card = nullptr;  // aggregation
    ScoringStrategy* m_mode = nullptr;  // Bricolage pour compiler le projet
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

public:
	void obtainScore(Cards card, Wildlife type);
    // un patron pour trouver les composantes (GameTile ou WildlifeToken) adjacentes avec le filtre choisi (biome ou animal)
    template <typename Component, typename Type>
    std::vector<std::vector<Component*>> getAdjacentComponents(const std::vector<std::vector<Component*>>& components, Type filter, int size = MAX_SIZE) const;
};



template <typename Component, typename Type>
std::vector<std::vector<Component*>> Score::getAdjacentComponents(const std::vector<std::vector<Component*>>& components, Type filter, int size) const {
    /* idée : on retrouve la HexCell associée à la GameTile ou (de manière plus importante) du WildlifeToken, puis on récupère les voisins de cette cellule, ensuite pour chaque voisin,
    * on regarde ses coordonnées Offset (s'ils existent) dans le tableau 2D et finalement on récupère la GameTile ou WildlifeToken à cet endroit pour effectuer le Union Find
    */
    Score::UnionFind uf(Component::MAX_ID + 1);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            Component* component = components[y][x];
            if (component == nullptr || component->getType() != filter) {
                continue;
            }
            int id = component->getId();
            // traitement voisins
            auto neighs = component->getNeighbors();
            for (size_t i = 0; i < neighs.size(); i++) {
                HexCell neighHex = neighs[i];
                PlayerBoard::Offset off = PlayerBoard::axialToOffset(neighHex);
                int off_x = off.getCol();
                int off_y = off.getRow();
                if (off_x < 0 || off_x >= size || off_y < 0 || off_y >= size)  // vérification que les coordonnées du voisin sont valides
                    continue;
                Component* n = components[off_y][off_x];  // le voisin du Component courant c
                if (n == nullptr || n->getType() != filter) {
                    continue;
                }
                uf.unite(id, n->getId());
            }
        }
    }
    // maintenant, on va regrouper les Component par parent (représentatif c.f. vidéo que j'ai envoyé sur Union Find)
    std::vector<std::vector<Component*>> buckets(Component::MAX_ID + 1);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Component* c = components[y][x];
            if (!c || c->getType() != filter)  // redondant mais au cas où
                continue;
            int root = uf.find(c->getId());
            buckets[root].push_back(c);
        }
    }
    // enfin, on va créer les vrais groupes, cette fois ci en supprimant aussi les indices ou c'est vide
    std::vector<std::vector<Component*>> groups;
    for (int id = 1; id <= Component::MAX_ID; id++) {
        if (!buckets[id].empty())
            groups.push_back(std::move(buckets[id]));
    }
    return groups;
}

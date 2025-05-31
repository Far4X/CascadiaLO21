#include "scoreutils.hpp"
// Bear cards
#include "bearscoringcards/bearscoringcarda.hpp"
#include "bearscoringcards/bearscoringcardb.hpp"
#include "bearscoringcards/bearscoringcardc.hpp"
#include "bearscoringcards/bearscoringcardd.hpp"

// Elk cards
#include "elkscoringcards/elkscoringcarda.hpp"
#include "elkscoringcards/elkscoringcardb.hpp"
#include "elkscoringcards/elkscoringcardc.hpp"
#include "elkscoringcards/elkscoringcardd.hpp"

// Fox cards
#include "foxscoringcards/foxscoringcarda.hpp"
#include "foxscoringcards/foxscoringcardb.hpp"
#include "foxscoringcards/foxscoringcardc.hpp"
#include "foxscoringcards/foxscoringcardd.hpp"

// Hawk cards
#include "hawkscoringcards/hawkscoringcarda.hpp"
#include "hawkscoringcards/hawkscoringcardb.hpp"
#include "hawkscoringcards/hawkscoringcardc.hpp"
#include "hawkscoringcards/hawkscoringcardd.hpp"

// Salmon cards
#include "salmonscoringcards/salmonscoringcarda.hpp"
#include "salmonscoringcards/salmonscoringcardb.hpp"
#include "salmonscoringcards/salmonscoringcardc.hpp"
#include "salmonscoringcards/salmonscoringcardd.hpp"

#include <cassert>
#include <set>
#include <algorithm>

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
                    return std::make_unique<ElkScoringCardA>();
                case 'B' :
                    return std::make_unique<ElkScoringCardB>();
                case 'C' :
                    return std::make_unique<ElkScoringCardC>();
                case 'D' :
                    return std::make_unique<ElkScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else if (animal == "Hawk") {
            switch(code) {
                case 'A' :
                    return std::make_unique<HawkScoringCardA>();
                case 'B' :
                    return std::make_unique<HawkScoringCardB>();
                case 'C' :
                    return std::make_unique<HawkScoringCardC>();
                case 'D' :
                    return std::make_unique<HawkScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else if (animal == "Fox") {
            switch(code) {
                case 'A' :
                    return std::make_unique<FoxScoringCardA>();
                case 'B' :
                    return std::make_unique<FoxScoringCardB>();
                case 'C' :
                    return std::make_unique<FoxScoringCardC>();
                case 'D' :
                    return std::make_unique<FoxScoringCardD>();
                    default:
                throw "invalid code";
            }
        }
        else if (animal == "Salmon") {
            switch(code) {
                case 'A' :
                    return std::make_unique<SalmonScoringCardA>();
                case 'B' :
                    return std::make_unique<SalmonScoringCardB>();
                case 'C' :
                    return std::make_unique<SalmonScoringCardC>();
                case 'D' :
                    return std::make_unique<SalmonScoringCardD>();
                default:
                    throw "invalid code";
            }
        }
        else {
            throw "invalid animal";
        }
    }

    // lines
    std::vector<HexCell> line_1 = {HexCell(0, 0)};
    std::vector<HexCell> line_2 = {HexCell(0, 0), HexCell(1, 0)};
    std::vector<HexCell> line_3 = {HexCell(0, 0), HexCell(1, 0), HexCell(2, 0)};
    std::vector<HexCell> line_4 = {HexCell(0, 0), HexCell(1, 0), HexCell(2, 0), HexCell(3, 0)};

    // triangle
    std::vector<HexCell> triangle = {HexCell(0, 0), HexCell(1, 0), HexCell(0, 1)};

    // diamond
    std::vector<HexCell> diamond = {HexCell(0, 0), HexCell(1, 0), HexCell(0, 1), HexCell(1, 1)};

    // ring
    std::vector<HexCell> ring = {HexCell(0, 0), HexCell(1, 0), HexCell(1, -1), HexCell(0, -1), HexCell(-1, 0), HexCell(-1, 1)};

    std::vector<std::vector<HexCell>> shapes_b = { line_1, line_2, triangle, diamond };


    TileGrid gatherAllTiles(const PlayerBoard& board, int size) {
        TileGrid tiles(size, std::vector<GameTile*>(size, nullptr));
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                tiles[y][x] = board.getOffsetTile(x, y);
            }
        }
        return tiles;
    }

    bool shareTile(const std::vector<GameTile*>& a, const std::vector<GameTile*>& b) {
        for (auto t1 : a) {
            for (auto t2 : b) {
                if (t1 == t2) {
                    return true;
                }
            }
        }
        return false;
    }

    // Création de l'UnionFind avec les tuiles élaguées
    UnionFind buildUnionFind(const PlayerBoard& board, int size, const AdjacencyPolicy& policy, TileGrid& tiles) {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                GameTile* tile = board.getOffsetTile(x, y);
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
            [&board, filter](GameTile* curr, GameTile* neigh) {
                for (int side = 0; side < 6; side++) {
                    Direction d = static_cast<Direction>(side);
                    if (board.getNeighborTile(*curr, d) != neigh) {
                        continue;
                    }
                    int opp_side = (side + 3) % 6;
                    return curr->getBiome(side) == filter && neigh->getBiome(opp_side) == filter;
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

    // fonction qui modifie les paramètres candidates et points pour y mettre toute les lignes candidates et les points correspondants
    void getLineFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup) {
        TileGrid groups = getComponents(board, size, makeSingletonPolicy(filter));
        std::vector<GameTile*> elks = flatten(groups);

        for (GameTile* elk : elks) {
            for (int i = 0; i < 6; i++) {
                std::vector<GameTile*> line;
                GameTile* curr = elk;

                for (int len = 1; len <= 4; len++) {
                    if (!curr || !curr->matchesType(filter)) {
                        break;
                    }
                    line.push_back(curr);  // on construit la ligne petit à petit
                    candidates.push_back(line);  // la ligne se reset chaque iteration pour accomoder des lignes de plus en plus grandes
                    points.push_back(points_lookup[len]);
                    curr = board.getNeighborTile(*curr, static_cast<Direction>(i));
                }
            }
        }
    }

    // fonction qui modifie les paramètres candidates et points pour y mettre toute les formes (ligne, triangle, losange) candidates et les points correspondants
    void getShapeFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup) {
        TileGrid groups = getComponents(board, size, makeSingletonPolicy(filter));
        std::vector<GameTile*> elks = flatten(groups);
        std::vector<std::vector<HexCell>> shapes = shapes_b;
        std::vector<std::vector<HexCell>> all_templates = getAllTemplates(shapes);

        for (const auto& shape : all_templates) {
            int shape_size = static_cast<int>(shape.size());
            int shape_score = points_lookup[shape_size];

            // anchor represente la tuile de depart pour la verification de la forme
            for (GameTile* anchor : elks) {
                std::vector<GameTile*> hit;
                bool ok = true;

                int q0 = anchor->getQ();
                int r0 = anchor->getR();

                // pour chaque dr, dq
                for (const HexCell& off : shape) {
                    int q = q0 + off.getQ();
                    int r = r0 + off.getR();
                    GameTile* tile = findTile(elks, q, r);
                    if (tile == nullptr) {
                        ok = false;
                        break;
                    }
                    hit.push_back(tile);
                }
                if (ok) {
                    candidates.push_back(hit);
                    points.push_back(shape_score);
                }
            }
        }
    }

    // fonction qui modifie les paramètres candidates et points pour y mettre tous les anneaux et sous-anneaux candidats et les points correspondants
    void getRingFormations(const PlayerBoard& board, int size, Wildlife filter, TileGrid& candidates, std::vector<int>& points, const std::vector<int>& points_lookup) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                GameTile* center = board.getOffsetTile(x, y);
                if (center == nullptr || center->matchesType(filter)) {
                    continue;
                }
                auto neighbors = board.getNeighborTiles(*center);
                std::vector<GameTile*> filter_neighbors;
                for (GameTile* tile : neighbors) {
                    if (tile != nullptr && tile->matchesType(filter)) {
                        filter_neighbors.push_back(tile);
                    }
                }
                // technique classique de subset avec un bitmask (ex : A, B, C, AB, AC, BC, ABC)
                int m = filter_neighbors.size();
                for (int mask = 1; mask < (1 << m); ++mask) {
                    std::vector<GameTile*> subset;
                    for (int b = 0; b < m; b++) {
                        if (mask & (1 << b)) {
                            subset.push_back(filter_neighbors[b]);
                        }
                    }
                    candidates.push_back(subset);
                    points.push_back(points_lookup[subset.size()]);
                }
            }
        }
    }


    void dfs(int idx, int curr_score, int& best_score, const std::vector<int>& points, const TileGrid& candidates, std::unordered_set<GameTile*>& used) {
        if (idx == static_cast<int>(candidates.size())) {  // cas de base : si on a parcouru tous les candidats
            if (curr_score > best_score) {
                best_score = curr_score;
            }
            return;
        }

        dfs(idx + 1, curr_score, best_score, points, candidates, used);  // pour le backtracking

        bool conflict = false;
        for (GameTile* tile : candidates[idx]) {
            if (used.count(tile)) {
                conflict = true;
                break;
            }
        }
        if (!conflict) {
            for (GameTile* tile : candidates[idx]) {
                used.insert(tile);
            }
            dfs(idx + 1, curr_score + points[idx], best_score, points, candidates, used);
        }

        for (GameTile* tile : candidates[idx]) {
            used.erase(tile);
        }
    }

    // fonction qui retoune une liste de tuples représentant les couples d'aigles qui partagent une line of sight (sans doublons)
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

    // fonction qui retourne les différentes orientations (uniques) d'une forme (parmi celles spécifiées par scoring card Elk)
    std::vector<std::vector<HexCell>> getOrientations(const std::vector<HexCell>& shape) {
        std::set<std::vector<HexCell>> unique_rot;
        std::vector<HexCell> curr = shape;
        for(int k = 0; k < 6; k++) {
            std::sort(curr.begin(), curr.end());
            unique_rot.insert(curr);
            for (auto &h : curr) {
                h = h.rotate60();
            }
        }
        return { unique_rot.begin(), unique_rot.end() };  // on construit un vecteur à partir du set (reordonné et sans doublons)
    }

    // fonction qui retourne toutes les orientations possibles de toutes les formes
    std::vector<std::vector<HexCell>> getAllTemplates(const std::vector<std::vector<HexCell>>& shapes) {
        std::vector<std::vector<HexCell>> templates;
        for (const auto& shape : shapes) {
            auto orientations = getOrientations(shape);
            for (const auto& orientation : orientations) {
                templates.push_back(orientation);
            }
        }
        return templates;
    }

    int countUniqueTokensBetween(const PlayerBoard& board, GameTile* a, GameTile* b, Wildlife filter) {
        assert(a != nullptr && b!= nullptr);
        std::unordered_set<Wildlife> seen_animals;
        HexCell step = HexCell::directionTo(*a, *b);
        HexCell cursor = *a;
        while (true) {
            cursor += step;
            if (cursor == *b) {
                break;
            }
            GameTile* tile = board.getTile(cursor.getQ(), cursor.getR());
            if (tile != nullptr && !tile->matchesType(filter)) {
                seen_animals.insert(tile->getToken()->getWildlifeType());
            }
        }
        return static_cast<int>(seen_animals.size());
    }
}

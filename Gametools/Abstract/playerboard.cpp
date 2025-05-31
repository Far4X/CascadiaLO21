#include "playerboard.hpp"
#include <iostream>
#include <set>


PlayerBoard::PlayerBoard(NotifiableInterface *tar) : TileHolder(MAX_SIZE, MAX_SIZE){
    m_target = tar;
}

GameTile* PlayerBoard::getNeighborTile(const GameTile& tile, Direction d) const {
    /*Permet de récupérer une tuile voisine*/
    HexCell hex = tile.getNeighbor(d);
    GameTile::Offset off = PlayerBoard::axialToOffset(hex);
    return this->getTile(off.getCol(), off.getRow());
}

std::vector<GameTile*> PlayerBoard::getNeighborTiles(const GameTile& tile) const {
    /*Permet de récupérer les voisins d'une tuile. Utile pour le scoring*/
    std::vector<HexCell> hexes = tile.getNeighbors();
    std::vector<GameTile*> neighbors;
    for (const HexCell& hex : hexes) {
        GameTile::Offset off = PlayerBoard::axialToOffset(hex);
        neighbors.push_back(getTile(off.getCol(), off.getRow()));
    }
    return neighbors;
}

int PlayerBoard::getNbNeighbors(const GameTile& tile) const {
    std::vector<GameTile*> neighbors = getNeighborTiles(tile);
    int count = 0;
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (neighbors[i] != nullptr) {
            count++;
        }
    }
    return count;
}

int PlayerBoard::getNbSameNeighbors(const GameTile& tile, Wildlife animal) const {
    std::vector<GameTile*> neighbors = getNeighborTiles(tile);
    int count = 0;
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (neighbors[i] != nullptr && neighbors[i]->getToken()->getWildlifeType() == animal) {
            count++;
        }
    }
    return count;
}

std::string PlayerBoard::getSaveString() const { // genere un string qui permet de déchiffrer l'affichage
    std::string desc = "c:";
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (TileHolder::getTile(i, j) != nullptr){
                desc += std::to_string(TileHolder::getTile(i, j)->getId()) + ";";
            }
        }
    }
    return desc;
}

void PlayerBoard::addTile(GameTile& tile){
    /*Permet d'ajouter une tuile. La position de la tuile est donnée par les caractéristiques de cette dernière*/
    int x;
    int y;
    m_pos_last_tile = tile;
    GameTile::Offset offset_value(0, 0);
    offset_value = this->axialToOffset(HexCell(tile.getQ(), tile.getR()));
    x = offset_value.getCol();
    y = offset_value.getRow();

    TileHolder::addTile(tile, x, y, true);
}

void PlayerBoard::addToken(const WildlifeToken* token, HexCell& pos_target){
    /*Permet d'ajouter un token à une tuile*/
    getTile(pos_target.getQ(), pos_target.getR())->setWildLifeToken(token);
    m_pos_last_token = pos_target;
}

void PlayerBoard::removeLast(){
    /*Permet d'effectuer le retour arrière en cas de non-validation des changements*/
    if (m_pos_last_token != HexCell(MAX_SIZE+1, MAX_SIZE+1) && m_pos_last_tile != HexCell(MAX_SIZE+1, MAX_SIZE+1) ){
        getTile(m_pos_last_token.getQ(), m_pos_last_token.getR())->setWildLifeToken(nullptr);
        HexCell::Offset of = axialToOffset(m_pos_last_tile);
        removeTile(of.getCol(), of.getRow());
    }
    m_pos_last_token = HexCell(MAX_SIZE+1, MAX_SIZE+1);
    m_pos_last_tile = HexCell(MAX_SIZE+1, MAX_SIZE+1);
}


bool PlayerBoard::hasNeighbour(const HexCell& pos){
    /*Permet de savoir si une tuile a des voisins ou pas. Utile pour la pose des tuiles*/
    for (size_t i = 0; i < pos.getNeighbors().size(); i++){
        HexCell::Offset neight = axialToOffset(pos.getNeighbors()[i]);
        if (neight.getCol() >= 0 && neight.getRow() >= 0 && this->TileHolder::getTile(neight.getCol(), neight.getRow()) != nullptr){
            return true;
        }
    }
    return false;
}

GameTile* PlayerBoard::getTile(int const &q, int const &r) const{
    /*Permet de retourner une tuile grâce à sa position qr*/
    HexCell::Offset offset_pos = PlayerBoard::axialToOffset(HexCell(q, r));
    return TileHolder::getTile(offset_pos.getCol(), offset_pos.getRow());
}

GameTile* PlayerBoard::getOffsetTile(int const &x, int const &y) const{
    /*Permet de retourner une tuile grâce à sa position xy*/
    return TileHolder::getTile(x, y);
}

void PlayerBoard::pointCell(int q, int r) {
    m_pointed_cell = HexCell(q, r);
}

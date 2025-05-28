#include "playerboard.hpp"
#include <iostream>


PlayerBoard::PlayerBoard(NotifiableInterface *tar) : TileHolder(MAX_SIZE, MAX_SIZE){
    //m_q_center = MAX_SIZE/2;
    //m_r_center = MAX_SIZE/2;

    m_target = tar;
}

/*int PlayerBoard::floorDiv(int n) {
    // fonction utilitaire pour la forumule de conversion entre hex et offset (la division normale ne marche pas avec les negatifs de notre cas)
    if (n >= 0) {
        return n / 2;
    }
    else {
        return (n - 1) / 2;
    }
}*/

/*PlayerBoard::Offset PlayerBoard::axialToOffset(const HexCell& hex){
    int q = hex.getQ();
    int r = hex.getR();
    int col = q + MAX_SIZE/2;
    int row = r + floorDiv(q) + MAX_SIZE/2;
    return PlayerBoard::Offset(col, row);
}

HexCell PlayerBoard::offsetToAxial(const Offset& off){
    int col = off.getCol();
    int row = off.getRow();
    int q = col - MAX_SIZE/2;
    int r = row - floorDiv(q) - MAX_SIZE/2;
    return HexCell(q, r);
}*/


GameTile* PlayerBoard::getNeighborTile(const GameTile& tile, Direction d) const {
    HexCell hex = tile.getNeighbor(d);
    GameTile::Offset off = PlayerBoard::axialToOffset(hex);
    return this->getTile(off.getCol(), off.getRow());
}

std::vector<GameTile*> PlayerBoard::getNeighborTiles(const GameTile& tile) const {
    std::vector<HexCell> hexes = tile.getNeighbors();
    std::vector<GameTile*> neighbors;
    for (const HexCell& hex : hexes) {
        GameTile::Offset off = PlayerBoard::axialToOffset(hex);
        neighbors.push_back(getTile(off.getCol(), off.getRow()));
    }
    return neighbors;
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

/*void PlayerBoard::moveHz(short int step){
    if ((step >= 0 && m_r_center > step) || (step < 0 && m_q_center >= 2*step)){ //TODO: check if superior to MAXSIZE;
        m_q_center += 2*step;
        m_r_center -= 1;
    }
}

void PlayerBoard::moveVt(short int step){
    if (step + m_q_center > 0 && step + m_q_center < MAX_SIZE){
        m_q_center += step;
    }
}*/

void PlayerBoard::addTile(GameTile& tile){
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
    getTile(pos_target.getQ(), pos_target.getR())->setWildLifeToken(token);
    m_pos_last_token = pos_target;
}

void PlayerBoard::removeLast(){
    if (m_pos_last_token != HexCell(MAX_SIZE+1, MAX_SIZE+1) && m_pos_last_tile != HexCell(MAX_SIZE+1, MAX_SIZE+1) ){
        std::cout << "Rmv" << std::endl;
        getTile(m_pos_last_token.getQ(), m_pos_last_token.getR())->setWildLifeToken(nullptr);
        HexCell::Offset of = axialToOffset(m_pos_last_tile);
        removeTile(of.getCol(), of.getRow());
    }
    std::cout << "Out rmv" << std::endl;
    m_pos_last_token = HexCell(MAX_SIZE+1, MAX_SIZE+1);
    m_pos_last_tile = HexCell(MAX_SIZE+1, MAX_SIZE+1);
}


bool PlayerBoard::hasNeighbour(const HexCell& pos){
    for (size_t i = 0; i < pos.getNeighbors().size(); i++){
        HexCell::Offset neight = axialToOffset(pos.getNeighbors()[i]);
        //std::cout << "Offset pos neigh : " << neight.getCol() << " " << neight.getRow() << std::endl;
        if (neight.getCol() >= 0 && neight.getRow() >= 0 && this->TileHolder::getTile(neight.getCol(), neight.getRow()) != nullptr){
            return true;
        }
    }
    return false;
}

GameTile* PlayerBoard::getTile(int const &q, int const &r) const{
    HexCell::Offset offset_pos = PlayerBoard::axialToOffset(HexCell(q, r));
    //std::cout << "Offset pos : " << offset_pos.getCol() << " " << offset_pos.getRow() << std::endl;
    return TileHolder::getTile(offset_pos.getCol(), offset_pos.getRow());
}

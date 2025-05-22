#include "playerboard.hpp"
#include "../Tiling/gametile.hpp"

PlayerBoard::PlayerBoard() : TileHolder(MAX_SIZE, MAX_SIZE){
    m_q_center = MAX_SIZE/2;
    m_r_center = MAX_SIZE/2;
}

int PlayerBoard::floorDiv(int n) {
    // fonction utilitaire pour la forumule de conversion entre hex et offset (la division normale ne marche pas avec les negatifs de notre cas)
    if (n >= 0) {
        return n / 2;
    }
    else {
        return (n - 1) / 2;
    }
}

PlayerBoard::Offset PlayerBoard::axialToOffset(const HexCell& hex){
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
}


GameTile* PlayerBoard::getNeighborTile(const GameTile& tile, Direction d) const {
    HexCell hex = tile.getNeighbor(d);
    PlayerBoard::Offset off = PlayerBoard::axialToOffset(hex);
    return this->getTile(off.getCol(), off.getRow());
}

std::vector<GameTile*> PlayerBoard::getNeighborTiles(const GameTile& tile) const {
    std::vector<HexCell> hexes = tile.getNeighbors();
    std::vector<GameTile*> neighbors;
    for (const HexCell& hex : hexes) {
        PlayerBoard::Offset off = PlayerBoard::axialToOffset(hex);
        neighbors.push_back(getTile(off.getCol(), off.getRow()));
    }
    return neighbors;
}

std::string PlayerBoard::getSaveString() const { // genere un string qui permet de déchiffrer l'affichage
    std::string desc = "c:";
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (getTile(i, j) != nullptr){
                desc += std::to_string(getTile(i, j)->getId()) + ";";
            }
        }
    }
    return desc;
}

void PlayerBoard::show(){

}


void PlayerBoard::moveHz(short int step){
    if ((step >= 0 && m_r_center > step) || (step < 0 && m_q_center >= 2*step)){ //TODO: check if superior to MAXSIZE;
        m_q_center += 2*step;
        m_r_center -= 1;
    }
}

void PlayerBoard::moveVt(short int step){
    if (step + m_q_center > 0 && step + m_q_center < MAX_SIZE){
        m_q_center += step;
    }
}

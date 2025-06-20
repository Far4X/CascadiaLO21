#include "playerboard.hpp"
#include <iostream>
#include <iostream>


PlayerBoard::PlayerBoard(NotifiableInterface *tar) : TileHolder(MAX_SIZE, MAX_SIZE){
    m_target = tar;
}

PlayerBoard::~PlayerBoard() {}

void PlayerBoard::show() {}

GameTile* PlayerBoard::getNeighborTile(const GameTile& tile, Direction d) const {
    /*Permet de récupérer une tuile voisine*/
    HexCell hex = tile.getNeighbor(d);
    return getTile(hex.getQ(), hex.getR());
}

std::vector<GameTile*> PlayerBoard::getNeighborTiles(const GameTile& tile) const {
    /*Permet de récupérer les voisins d'une tuile. Utile pour le scoring*/
    std::vector<HexCell> hexes = tile.getNeighbors();
    std::vector<GameTile*> neighbors;
    for (const HexCell& hex : hexes) {
        neighbors.push_back(getTile(hex.getQ(), hex.getR()));
    }
    return neighbors;
}

int PlayerBoard::getNbNeighbors(const GameTile& tile) const {
    //Retourne les voisins d'une tuile, dans le contexte d'un plateau de joueurs.
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
        if (neighbors[i] != nullptr && neighbors[i]->getToken() != nullptr && neighbors[i]->getToken()->getWildlifeType() == animal) {
            count++;
        }
    }
    return count;
}

std::string PlayerBoard::getSaveString() const { // genere un string qui permet de déchiffrer l'affichage
    std::string desc = "{";
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (TileHolder::getTile(i, j) != nullptr){
                desc += std::to_string(TileHolder::getTile(i, j)->getId()) + "," + std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(TileHolder::getTile(i, j)->getRotation()) + ",";
                if (TileHolder::getTile(i, j)->getToken() != nullptr){
                    desc += std::to_string(TileHolder::getTile(i, j)->getToken()->getWildlifeType());
                }
                else {
                    desc += "100";
                }
                desc += ";";
            }
        }
    }
    desc += "}";
    return desc;
}


void PlayerBoard::reinterpretString(const std::string &desc){
    //Permet de ressuciter le tableau d'un joueur à partir de la chaine de caractère descriptive enregistrée
    std::vector<std::string> params = separateParams(desc);
    for (size_t i = 0; i < params.size(); i++){
        std::vector<std::string> tile_params = separateParams(params[i], ',');
        if (tile_params.size() != 5){
            throw CustomError("Parameter number for ressuciting PlayerBoard not good : "  + desc, 99);
        }
        m_required_cards.push_back(std::tuple(stringToInt(tile_params[0]), stringToInt(tile_params[1]), stringToInt(tile_params[2]), stringToInt(tile_params[3]), stringToInt(tile_params[4])));
    }
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

const GameTile* PlayerBoard::getLast(){
    return getTile(m_pos_last_token.getQ(), m_pos_last_token.getR());
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
    HexCell::Offset poso = axialToOffset(pos);
    //std::cout << "Self : " << poso.getCol() << ", " << poso.getRow() << std::endl;
    for (size_t i = 0; i < pos.getNeighbors().size(); i++){
        HexCell::Offset neight = axialToOffset(pos.getNeighbors()[i]);
        //std::cout << "Checking neight : " << neight.getCol() << ", " << neight.getRow() << std::endl;
        if (neight.getCol() >= 0 && neight.getRow() >= 0 && this->TileHolder::getTile(neight.getCol(), neight.getRow()) != nullptr){
            return true;
        }
    }
    return false;
}

GameTile* PlayerBoard::getTile(int const &q, int const &r) const{
    /*Permet de retourner une tuile grâce à sa position qr*/
    HexCell::Offset offset_pos = PlayerBoard::axialToOffset(HexCell(q, r));
    int col = offset_pos.getCol();
    int row = offset_pos.getRow();

    if (col < 0 || col >= m_size_x || row < 0 || row >= m_size_y) {
        return nullptr;
    }
    return TileHolder::getTile(col, row);
}

GameTile* PlayerBoard::getOffsetTile(int const &x, int const &y) const{
    /*Permet de retourner une tuile grâce à sa position xy*/
    if (x < 0 || x >= m_size_x || y < 0 || y >= m_size_y) {
        return nullptr;
    }
    return TileHolder::getTile(x, y);
}

void PlayerBoard::pointCell(int q, int r) {
    m_pointed_cell = HexCell(q, r);
}

std::tuple<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int> PlayerBoard::getNextNeededCard(){
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int> rt = m_required_cards.back();
    m_required_cards.pop_back();
    return rt;
}

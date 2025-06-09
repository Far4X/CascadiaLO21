#include "tileholder.hpp"
#include <iostream>
#include <set>

TileHolder::TileHolder(int size_x, int size_y) : Printable(), SalvableThing(){
    m_size_x = size_x;
    m_size_y = size_y;
    m_tiles = new GameTile** [size_x];
    for (int i = 0; i < size_x; i++){
        m_tiles[i] = new GameTile* [size_y];
        for (int j = 0; j < size_y; j++){
            m_tiles[i][j] = nullptr;
        }
    }
}

TileHolder::~TileHolder(){
    for (int i = 0; i < m_size_x; i++){
        delete[] m_tiles[i];
    }
    delete[] m_tiles;
}

GameTile* TileHolder::getTile(int posx, int posy) const{
    /*Retourne une tuile en fonction de sa position (x,y)*/
    if (posx < m_size_x && posy < m_size_y){
        return (m_tiles[posx][posy]);
    }
    std::string txt = "Tile not in range; x : " + std::to_string(posx) + ", y : " + std::to_string(posy);
    throw CustomError(txt, 201);
}

void TileHolder::removeTile(int x, int y){
    /*Permet d'enlever une tuile du tableau*/
    m_tiles[x][y] = nullptr;
}


void TileHolder::addTile(GameTile& tile, int x, int y, bool overwrite){
    /*Permet d'ajouter une tuile au tableau*/
    if (x < 0 || y < 0) {
        throw CustomError("X or Y non positive", 202);
    }
    if (tile.getQ() >= m_size_x || tile.getR() >= m_size_y){
        throw CustomError("Holder not big enought", 201);
    }
    if (!overwrite && m_tiles[x][y] != nullptr){
        return;
    }

    m_tiles[x][y] = &tile;
}

TileHolder::Iterator& TileHolder::Iterator::operator++(int){
    m_x++;
    while(m_y < m_holder->m_size_y){
        while(m_x < m_holder->m_size_x){
            //std::cout << "Getting tile" << std::endl;
            if (m_holder->getTile(m_x, m_y) != nullptr){
                return *this;
            }
            //std::cout << "OE Getting tile" << std::endl;
            m_x++;
        }
        m_x = 0;
        m_y++;
    }
    return *this;
}

bool TileHolder::Iterator::isDone() const{
    /*unsigned short x = m_x+1;
    unsigned short y = m_y;

    while(y < m_holder->m_size_y){
        while(x < m_holder->m_size_x){
            if (m_holder->getTile(x, y) != nullptr){
                return false;
            }
            x++;

        }
        x = 0;
        y++;
    }
    std::cout << "RT" << std::endl;*/

    if (m_y == m_holder->m_size_y){
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> TileHolder::getFilledTilePositions() const {
    std::vector<std::pair<int, int>> filled;
    for (int x = 0; x < m_size_x; ++x) {
        for (int y = 0; y < m_size_y; ++y) {
            if (m_tiles[x][y] != nullptr) {
                filled.emplace_back(x, y);
            }
        }
    }
    return filled;
}


std::vector<HexCell> TileHolder::getFreeAdjacentCells(int max_size) const {
    std::set<HexCell> result;

    auto filledPositions = getFilledTilePositions();
    for (const auto& [x, y] : filledPositions) {
        // Conversion de (x, y) en HexCell
        HexCell center = HexCell::offsetToAxial(HexCell::Offset(x, y), max_size);

        // voisins en axial
        std::vector<HexCell> neighbors = center.getNeighbors();

        for (const HexCell& neighbor : neighbors) {
            // en coordonnées offset
            HexCell::Offset off = HexCell::axialToOffset(neighbor, max_size);

            int col = off.getCol();
            int row = off.getRow();

            // verif bornes
            if (col >= 0 && col < m_size_x && row >= 0 && row < m_size_y) {
                // si vide, ajouter à l’ensemble
                if (m_tiles[col][row] == nullptr) {
                    result.insert(neighbor);
                }
            }
        }
    }
    return std::vector<HexCell>(result.begin(), result.end());
}


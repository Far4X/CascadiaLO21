#include "tileholder.hpp"

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
    if (posx < m_size_x && posy < m_size_y){
        return (m_tiles[posx][posy]);
    }
    throw CustomError("Tile not in range", 201);
}


void TileHolder::addTile(GameTile& tile, unsigned int* q, unsigned int* r, bool overwrite){
    if (q == nullptr || r == nullptr){
        if (m_tiles[tile.getQ()][tile.getR()] != nullptr && overwrite == false){
            throw CustomError("Tile overwrite not allowed", 202);
        }
        if (tile.getQ() >= m_size_x || tile.getR() >= m_size_y){
            throw CustomError("Holder not in range", 201);
        }
        m_tiles[tile.getQ()][tile.getR()] = &tile;
        return;
    }

    tile.setQ(*q);
    tile.setR(*r);
    if (tile.getQ() >= m_size_x || tile.getR() >= m_size_y){
        throw CustomError("Holder not big enought", 201);
    }

    m_tiles[*q][*r] = &tile;
}



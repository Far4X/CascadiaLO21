#include "tileholder.hpp"
#include <iostream>

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
    std::cout << "EPS : " << m_x << ", " << m_y << std::endl;
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


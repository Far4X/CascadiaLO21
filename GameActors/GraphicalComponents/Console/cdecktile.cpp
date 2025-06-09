#include "cdecktile.hpp"
#include <iostream>

CDeckTile& CDeckTile::getInstance(){
    static CDeckTile ins;
    return ins;
}

CDeckTile::CDeckTile() : DeckTile(){}


void CDeckTile::show(){
    for (int i = 0; i < 30; i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    //On génère le tableau qui va contenir les représentations des tuiles

    char **tab = new char*[m_max_height];
    for (int i = 0; i < m_max_height; i++){
        tab[i] = new char[m_max_width];
    }

    for (int i = 0; i < m_max_height; i++){
        for (int j = 0; j < m_max_width; j++){
            tab[i][j] = ' ';
        }
    }

    const unsigned short int tile_height = 2*m_size_tile+1;
    const unsigned short int tile_width = 4*m_size_tile;
    char **tile_rpr = new char*[tile_height];
    for (unsigned short int i = 0; i < tile_height; i++){
        tile_rpr[i] = new char[tile_width];
        for (int j = 0; j < tile_width; j++){
            tile_rpr[i][j] = ' ';
        }
    }
    //On récupère toutes les représentations des tuiles

    for (int i = 0; i < 4; i++){
        const GameTile* tile = getTile(i);
        if (tile == nullptr){
            throw CustomError("Tile doesn't exists", 999);
        }
        tile_rpr = getRepresentation(tile, m_size_tile, 4, false); // On récupère l'image de la tuile
        for (int j = 0; j < 2*m_size_tile +1; j++){
            for (int k = 0; k < 4*m_size_tile; k++){
                //if (tile[i][j] != ' ' || tab[base_y + i][base_x + j] == '*'){
                if (tab[2 + j][i * 5 * m_size_tile + k] == ' '){
                    tab[2 + j][i * 5 * m_size_tile + k] = tile_rpr[j][k];
                }
            }
        }
        char token = ' ';
        switch (m_displayed_tokens[i]->getWildlifeType()){
        case Hawk :
            token = 'H';
            break;
        case Elk :
            token = 'E';
            break;
        case Salmon :
            token = 'S';
            break;
        case Fox :
            token = 'F';
            break;
        case Bear :
            token = 'B';
            break;
        default :
            break;
        }
        tab[0][i * 5 * m_size_tile + m_size_tile] = token;
    }

    for (unsigned short int i = 0; i < tile_height; i++){
        delete[] tile_rpr[i];
    }
    delete[] tile_rpr;

    for (int i = 0; i < m_max_height; i++){
        for (int j = 0; j < m_max_width; j++){
            std::cout << tab[i][j];
        }
        std::cout << std::endl;
    }
}

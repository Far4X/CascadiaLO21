#include "cplayerboard.hpp"
#include <iostream>

CPlayerBoard::CPlayerBoard() : PlayerBoard(){}

void CPlayerBoard::show(){
    std::cout << "---" << std::endl;
    char **tab = new char*[m_max_height];
    for (int i = 0; i < m_max_height; i++){
        tab[i] = new char[m_max_width];
    }

    for (int i = 0; i < m_max_height; i++){
        for (int j = 0; j < m_max_width; j++){
            //tab[i][j] = '*'; dbg
            tab[i][j] = ' ';
        }
    }

    const unsigned short int tile_height = 2*m_size_tile+1;
    const unsigned short int tile_width = 4*m_size_tile;
    char **tile = new char*[tile_height];
    for (unsigned short int i = 0; i < tile_height; i++){
        tile[i] = new char[tile_width];
        for (int j = 0; j < tile_width; j++){
            tile[i][j] = ' ';
        }
    }
    int base_x = -m_x_swift;
    int base_y = -m_y_swift;
    for (int x = 0; x < MAX_SIZE; x++){
        for (int y = 0; y < MAX_SIZE; y++){
            //std::cout << base_x << "; " << base_y << std::endl;
            //std:: cout << (base_x >= 0) << (base_y >= 0) << (base_x + 4 * m_size_tile < m_max_width) << (base_y + 2*m_size_tile +1 < m_max_height) << std::endl;
            if (base_x >= 0 && base_y >= 0 && base_x + 4 * m_size_tile < m_max_width && base_y + 2*m_size_tile +1 < m_max_height){
                tile = getRepresentation(this->getTile(x, y), m_size_tile);
                //std::cout << "Print tile on " << x << "; " << y << std::endl;
                for (int i = 0; i < 2*m_size_tile +1; i++){
                    for (int j = 0; j < 4*m_size_tile; j++){
                        //if (tile[i][j] != ' ' || tab[base_y + i][base_x + j] == '*'){
                        if (tab[base_y + i][base_x + j] == ' '){
                            tab[base_y + i][base_x + j] = tile[i][j];
                        }
                    }
                }
            }
            base_y += m_size_tile * 2;
        }
        base_x += 3 * m_size_tile;
        if (x % 2 == 0){
            base_y = -m_size_tile -m_y_swift;
        }
        else {
            base_y = -m_y_swift;
        }
    }

    for (int i = 0; i < m_max_height; i++){
        for (int j = 0; j < m_max_width; j++){
            std::cout << tab[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < m_max_height; i++){
        delete[] tab[i];
    }
    delete[] tab;
}

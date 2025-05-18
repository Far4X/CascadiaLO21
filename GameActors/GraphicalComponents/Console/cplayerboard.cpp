#include "cplayerboard.hpp"
#include <iostream>

CPlayerBoard::CPlayerBoard() : PlayerBoard(){}

void CPlayerBoard::show(){
    reprBoard();
    std::cout << "---" << std::endl;

    bool continue_menu = true;


    while (continue_menu){
        std::cout << "Merci de saisir une des options suivantes : " << std::endl;
        std::cout << "0 : Passer" << std::endl;
        std::cout << "z : Se deplacer vers le haut" << std::endl;
        std::cout << "q : Se deplacer vers la gauche" << std::endl;
        std::cout << "s : Se deplacer vers le bas" << std::endl;
        std::cout << "d : Se deplacer vers la droite" << std::endl;

        std::string res;
        std::cin >> res;

        switch (res[0]) {
        case '0':
            continue_menu = false;
            break;
        case 'z':
            m_y_swift -= step;
            reprBoard();
            break;
        case 'q':
            m_x_swift -= step;
            reprBoard();
            break;
        case 's':
            m_y_swift += step;
            reprBoard();
            break;
        case 'd' :
            m_x_swift += step;
            reprBoard();
            break;
        default:
            std::cout << "Action non reconnue, merci de recommencer" << std::endl;
            break;
        }
    }

}

void CPlayerBoard::reprBoard(){
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
    char **tile_rpr = new char*[tile_height];
    for (unsigned short int i = 0; i < tile_height; i++){
        tile_rpr[i] = new char[tile_width];
        for (int j = 0; j < tile_width; j++){
            tile_rpr[i][j] = ' ';
        }
    }
    int base_x = -m_x_swift;
    int base_y = -m_y_swift;
    for (int x = 0; x < MAX_SIZE; x++){
        for (int y = 0; y < MAX_SIZE; y++){
            //std::cout << base_x << "; " << base_y << std::endl;
            //std:: cout << (base_x >= 0) << (base_y >= 0) << (base_x + 4 * m_size_tile < m_max_width) << (base_y + 2*m_size_tile +1 < m_max_height) << std::endl;
            if (base_x >= 0 && base_y >= 0 && base_x + 4 * m_size_tile < m_max_width && base_y + 2*m_size_tile +1 < m_max_height){
                GameTile* tile = this->getTile(x, y);
                if (tile != nullptr){
                    tile_rpr = getRepresentation(tile, m_size_tile, MAX_SIZE);
                    //std::cout << "Print tile on " << x << "; " << y << std::endl;

                }
                else {
                    HexCell cell = HexCell::offsetToAxial(HexCell::Offset(x, y), MAX_SIZE);
                    tile_rpr = getRepresentationCell(&cell, m_size_tile, MAX_SIZE);
                }
                for (int i = 0; i < 2*m_size_tile +1; i++){
                    for (int j = 0; j < 4*m_size_tile; j++){
                        //if (tile[i][j] != ' ' || tab[base_y + i][base_x + j] == '*'){
                        if (tab[base_y + i][base_x + j] == ' '){
                            tab[base_y + i][base_x + j] = tile_rpr[i][j];
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

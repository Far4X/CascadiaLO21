#include "cplayerboard.hpp"
#include <iostream>

CPlayerBoard::CPlayerBoard(NotifiableInterface *tar) : PlayerBoard(tar){}

CPlayerBoard::CPlayerBoard(NotifiableInterface *tar, const std::string& def) : PlayerBoard(tar){
    reinterpretString(def);
}


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
        std::cout << "p : Pointer une tuile/un emplacement" << std::endl;


        std::string res;
        std::cin >> res;
        unsigned short int x = 0;
        unsigned short int y = 0;

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
        case 'p' :
            std::cout << "Merci de choisir les coordonnées en x : ";
            std::cin >> res;

            if (res.size() == 1 && res[0] >= '0' && res[0] <= '9'){
                x = char(res[0]) - '0';
            }
            else if (res.size() == 2 && res[0] >= '0' && res[0] <= '9' && res[1] >= '0' && res[1] <= '9'){
                x = (char(res[0]) - '0') * 10;
                x += char(res[1]) - '0';
            }
            else {
                break;
            }

            std::cout << "Merci de choisir les coordonnées en y : ";
            std::cin >> res;

            if (res.size() == 1 && res[0] >= '0' && res[0] <= '9'){
                y = char(res[0]) - '0';
            }
            else if (res.size() == 2 && res[0] >= '0' && res[0] <= '9' && res[1] >= '0' && res[1] <= '9'){
                y = (char(res[0]) - '0') * 10;
                y += char(res[1]) - '0';
            }
            else {
                break;
            }

            m_pointed_cell = offsetToAxial(HexCell::Offset(x, y));
            break;
        default:
            std::cout << "Action non reconnue, merci de recommencer" << std::endl;
            break;
        }
    }

    m_target->notifyInterface(4);
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
    int base_y = -m_y_swift - m_size_tile;
    for (int x = 0; x < MAX_SIZE; x++){
        for (int y = 0; y < MAX_SIZE; y++){
            //std::cout << base_x << "; " << base_y << std::endl;
            //std:: cout << (base_x >= 0) << (base_y >= 0) << (base_x + 4 * m_size_tile < m_max_width) << (base_y + 2*m_size_tile +1 < m_max_height) << std::endl;
            if (base_x >= 0 && base_y >= 0 && base_x + 4 * m_size_tile < m_max_width && base_y + 2*m_size_tile +1 < m_max_height){
                GameTile* tile = this->TileHolder::getTile(x, y);
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
        if (x % 2 == 1){
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

    for (unsigned short int i = 0; i < tile_height; i++){
        delete[] tile_rpr[i];
    }
    delete[] tile_rpr;

    for (int i = 0; i < m_max_height; i++){
        delete[] tab[i];
    }
    delete[] tab;
}

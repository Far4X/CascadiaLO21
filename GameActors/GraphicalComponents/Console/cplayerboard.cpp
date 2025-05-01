#include "cplayerboard.hpp"
#include <iostream>

CPlayerBoard::CPlayerBoard() : PlayerBoard(){}

void CPlayerBoard::show(){
    char **tab = new char*[m_max_width];
    for (int i = 0; i < m_max_width; i++){
        tab[i] = new char[m_max_height];
    }

    for (int i = 0; i < m_max_width; i++){
        for (int j = 0; j < m_max_height; j++){
            tab[i][j] = '*';
        }
    }

    for (int i = 0; i < m_max_width; i++){
        for (int j = 0; j < m_max_height; j++){
            std::cout << tab[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < m_max_width; i++){
        delete[] tab[i];
    }
    delete[] tab;
}

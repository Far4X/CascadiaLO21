#include "cplayerboard.hpp"

CPlayerBoard::CPlayerBoard() {}

void CPlayerBoard::show(){
    char **tab = new char*[m_max_width];
    for (int i = 0; i < m_max_width; i++){
        tab[i] = new char[m_max_height];
    }

    for (int i = 0; i < m_max_width; i++){
        delete[] tab[i];
    }
    delete[] tab;
}

void CPlayerBoard::swiftX(short int step){
    if (m_x_swift >= -step){
        m_x_swift += step;
    }
}

void CPlayerBoard::swiftY(short int step){
    if (m_y_swift >= -step){
        m_y_swift += step;
    }
}

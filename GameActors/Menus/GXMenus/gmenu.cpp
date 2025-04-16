#include "gmenu.hpp"

template <typename T>
GMenu<T>::GMenu(unsigned int size_x, unsigned int size_y, unsigned int pos_x, unsigned int pos_y) : QWidget, Menu<T>(){
    m_size_x = size_x;
    m_size_y = size_y;
    m_pos_x = pos_x;
    m_pos_y = pos_y;
    actualize();
}

template <typename T>
void GMenu<T>::actualize(){
    this->setGeometry(m_size_x, m_size_y, pos_x, pos_y);
}


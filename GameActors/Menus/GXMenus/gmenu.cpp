#include "gmenu.hpp"

template <typename T>
GMenu<T>::GMenu(NotifiableInterface* target, QWidget* parent, unsigned int size_x, unsigned int size_y, unsigned int pos_x, unsigned int pos_y) : QWidget(parent), Menu<T>(target){
    if (target == nullptr){
        throw CustomError("Target can't be nullptr", 203);
    }
    m_size_x = size_x;
    m_size_y = size_y;
    m_pos_x = pos_x;
    m_pos_y = pos_y;
    actualize();
}

template <typename T>
void GMenu<T>::actualize(){
    this->setGeometry(m_size_x, m_size_y, m_pos_x, m_pos_y);
}

template <typename T>
void GMenu<T>::show(){
    QWidget::show();
}

template class GMenu<std::string>;
template class GMenu<std::tuple<std::string, std::string>>;

#include "menu.hpp"
#include <string>

#include <iostream>

template <typename T>
Menu<T>::Menu(NotifiableInterface* target) : Printable(){
    if (target == nullptr){
        throw CustomError("No target found for menu", 300);
        //std::cout << "STNPTR" << std::endl;
    }
    m_target = target;
}

template <typename T>
Menu<T>::~Menu(){
    delete[] m_results;
}

template <typename T>
void Menu<T>::addResult(const T& tar){
    /*Permet d'ajouter un résultat au menu*/
    T* new_t = new T [m_nb_result + 1];
    for (int i = 0; i < m_nb_result; i++){
        new_t[i] = m_results[i];
    }
    delete[] m_results;
    m_results = new_t;
    m_results[m_nb_result++] = tar;
}

template <typename T>
typename Menu<T>::Iterator Menu<T>::getIterator() const {
    return Iterator(*this);
}


template class Menu<std::string>;
template class Menu<std::tuple<std::string, std::string>>;
template class Menu<unsigned short int>;
template class Menu<bool>;



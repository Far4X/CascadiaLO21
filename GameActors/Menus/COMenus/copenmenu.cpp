#include "copenmenu.hpp"

COpenMenu::COpenMenu() : CMenu(){

}

void COpenMenu::print() const{
    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    std::cout << "Merci de saisir un nombre de joueurs ci-après : " << std::endl;

    std::cin >> m_raw_out;


    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool COpenMenu::checkResult(){

}

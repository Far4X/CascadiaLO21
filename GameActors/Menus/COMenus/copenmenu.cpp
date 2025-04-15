#include "copenmenu.hpp"

COpenMenu::COpenMenu() : CMenu(){

}

void COpenMenu::print() const{
    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;
    while (m_result <= 0 || m_result > 4){
        std::cout << "Merci de saisir un nombre de joueurs ci-après (1-4) : " << std::endl;
        std::cin >> m_result;
    }

    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool COpenMenu::checkResult(){

}

#include "cplayermenu.hpp"
#include <iostream>

CPlayerMenu::CPlayerMenu() : CMenu(){

}

void CPlayerMenu::show() {
    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;


    std::cout << "Merci de saisir un nombre de joueurs ci-apres (1-4) : " << std::endl;
    std::string res;
    std::cin >> res;

    if (res[0] >= '1' && res[0] <= '4'){
        m_result = res[0] - '0';
    }
    else {
        throw CustomError("L'utilisateur n'a pas entré un nombre", 300);
    }

    std::cin.ignore();
    std::cout << "Nombre de joueurs : " << m_result << std::endl;
    std::string name;
    for (int i = 0; i < m_result; i++){
        std::cout << "Merci d'entrer le nom du joueur numéro " << i+1 << " : ";
        std::cin >> name;
        addResult(name);
    }

    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

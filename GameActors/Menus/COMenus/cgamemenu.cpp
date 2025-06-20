#include "cgamemenu.hpp"
#include <iostream>

CGameMenu::CGameMenu(NotifiableInterface *tar) : CMenu<std::tuple<std::string, std::string>>(tar) {

}

void CGameMenu::show(){
    for (unsigned int i = 0; i < getX(); i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    bool continue_menu = true;

    //std::cin.ignore();

    while (continue_menu){
        std::cout << "Merci de saisir une des options suivantes : " << std::endl;
        std::cout << "0 : Jouer" << std::endl;
        std::cout << "1 : Charger la dernière partie" << std::endl;
        std::cout << "2 : Utiliser une variante " << std::endl;
        std::cout << "3 : Choisir les cartes de marquage points" << std::endl;

        std::string res;
        std::cin >> res;

        switch (res[0]) {
        case '0':
            continue_menu = false;
            break;
        case '1':
            this->addResult(std::tuple<std::string, std::string>("Recover", "true"));
            continue_menu = false;
            break;
        case '2':
            std::cout << "Merci de rentrer la variante que vous voulez utiliser (F/f pour famille, I/i pour intermediaire)" << std::endl;
            std::cin >> res;
            if (res == "f" || res == "F" || res == "i" || res == "I"){
                this->addResult(std::tuple<std::string, std::string>("Use variant", res));
                continue_menu = false;
            }
            else {
                std::cout << "Valeur entrée non valide, les changements n'ont pas été pris en compte." << std::endl;
            }
            break;
        case '3':
            std::cout << "Merci de rentrer l'identifiant des cartes dans l'ordre Ours, Elan, Aigle, Renard, Saumon (ex : ABCDA)" << std::endl;
            std::cin >> res;
            if (res.size() >= 5){
                this->addResult(std::tuple<std::string, std::string>("Use cards", res));
            }
            else {
                std::cout << "Valeur entrée non valide, les changements n'ont pas été pris en compte." << std::endl;
            }
            break;
        default:
            std::cout << "Action non reconnue, merci de recommençer" << std::endl;
            break;
        }
    }

    m_target->notifyInterface(2);
}

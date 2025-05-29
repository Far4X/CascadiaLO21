#include "cvalidatemenu.hpp"
#include "cmenu.hpp"
#include <iostream>

CValidateMenu::CValidateMenu(NotifiableInterface* tar) : CMenu(tar) {

}

void CValidateMenu::show(){
    bool cnt = true;
    std::cout << "Merci de valider les opérations effectuées" << std::endl;
    while (cnt){
        std::cout << "Entrez y/n : ";
        std::string in;
        std::cin >> in;
        if (in[0] == 'y'){
            addResult(true);
            cnt = false;
        }
        else if (in[0] == 'n'){
            addResult(false);
            cnt = false;
        }
    }
    m_target->notifyInterface(5);
    std::cout << "Notified 5" << std::endl;
}

#include "ctokenmenu.hpp"
#include <iostream>

CTokenMenu::CTokenMenu(NotifiableInterface* tar, DeckTile* decktile, Player* caller) : CMenu(tar), m_caller(caller){
    m_deck_tile = decktile;
}

void CTokenMenu::show(){
    m_deck_tile->show();

    std::cout << "Voulez-vous utiliser un pion nature; vous en avez : " << m_caller->getNbNatureToken() << ". n : Non, c : Enlever tous les jeton faune actuel, b : Prendre séparément pion faune et tuile" << std::endl;
    //TODO : Removetoken;
    //TODO : clear token if possible
    bool cnt = true;
    bool choose_distinc;
    std::string out;
    while (cnt){
        std::cin >> out;
        if (out.size() == 1 && out[0] == 'b'){
            m_caller->removeNatureToken();
            choose_distinc = true;
            cnt = false;
        }
        else if (out.size() == 1 && out[0] == 'n'){
            choose_distinc = false;
            cnt = false;
        }
        else if (out.size() == 1 && out[0] == 'c'){
            if (m_deck_tile->canFlushWithoutNaturetoken()){
                m_deck_tile->clearTokens();
                m_deck_tile->show();

            }
            else {
                choose_distinc = false;
                cnt = false;
                m_deck_tile->clearTokens();
                m_caller->removeNatureToken();
                m_deck_tile->show();

            }
        }
        else {
            std::cout << "Résultat non valide. Merci d'écrire n, c ou b." << std::endl;
        }
    }

    cnt = true;
    int id_tile;
    int id_token = -1;
    std::cout << "Quelle tuile voulez-vous choisir ? (1 à 4) : ";
    while (cnt){
        std::cin >> out;
        if (out.size() == 1 && out[0] > '0' && out[0] <= '4'){
            id_tile = out[0] - '1';
            cnt = false;
        }
        else {
            std::cout << "Résultat non valide. Merci d'écrire un nombre entre 1 et 4" << std::endl;
        }
    }
    this->addResult(id_tile);
    if (choose_distinc){
        std::cout << "Quelle jeton voulez-vous choisir ? (1 à 4) : ";
        while (cnt){
            std::cin >> out;
            if (out.size() == 1 && out[0] > '0' && out[0] <= '4'){
                id_token = out[0] - '1';
                cnt = false;
            }
            else {
                std::cout << "Résultat non valide. Merci d'écrire un nombre entre 1 et 4" << std::endl;
            }
        }
        this->addResult(id_token);
    }
    m_target->notifyInterface(3);
}


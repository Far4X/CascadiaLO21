#include "ctokenmenu.hpp"
#include <iostream>

CTokenMenu::CTokenMenu(NotifiableInterface* tar, DeckTile* decktile, Player* caller) : CMenu(tar), m_caller(caller){
    m_deck_tile = decktile;
}

void CTokenMenu::show(){
    m_deck_tile->show();

    std::cout << "Voulez-vous utiliser un pion nature; vous en avez : " << m_caller->getNbNatureToken() << ". n : Non, c : Enlever tous les jeton faune actuel, b : Prendre séparément pion faune et tuile" << std::endl;
    //TODO : Removetoken;
    bool cnt = true;
    bool choose_distinc;
    std::string out;
    while (cnt){
        std::cin >> out;
        if (out.size() == 1 && out[0] == 'b'){
            choose_distinc = true;
            cnt = false;
        }
        else if (out.size() == 1 && out[0] == 'n'){
            choose_distinc = false;
            cnt = false;
        }
        else if (out.size() == 1 && out[0] == 'c'){
            choose_distinc = false;
            cnt = false;

            //Clear tokens
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

    // Récupérer les emplacements disponibles en axial
    unsigned int max_size = getX();
    std::vector<HexCell> adjacentsDisponibles = m_caller->getBoard()->getFreeAdjacentCells(max_size);

    // Affichage
    std::cout << "Vous avez choisi la tuile numéro " << id_tile + 1 << ".\n\n";
    std::cout << "Où souhaitez-vous la placer ? Voici les emplacements disponibles autour de votre pion :\n\n";

    for (size_t i = 0; i < adjacentsDisponibles.size(); ++i) {
        // Conversion axial → offset
        HexCell::Offset off = HexCell::axialToOffset(adjacentsDisponibles[i], max_size);
        std::cout << i << " : (" << off.getCol() << ", " << off.getRow() << ") – Tuile vide\n";
    }

    // Choix utilisateur
    int choixPlacement = -1;
    bool saisieValide = false;

    while (!saisieValide) {
        std::cout << "\nVeuillez saisir le numéro de l’emplacement choisi : ";
        std::cin >> out;

        if (out.size() == 1 && isdigit(out[0])) {
            choixPlacement = out[0] - '0';
            if (choixPlacement >= 0 && static_cast<size_t>(choixPlacement) < adjacentsDisponibles.size()) {
                saisieValide = true;
            } else {
                std::cout << "Numéro hors plage. Essayez encore.\n";
            }
        } else {
            std::cout << "Entrée invalide. Merci d’écrire un chiffre valide.\n";
        }
    }

    // On enregistre les coordonnées converties dans les résultats
    HexCell::Offset coordChoisie = HexCell::axialToOffset(adjacentsDisponibles[choixPlacement], max_size);
    this->addResult(coordChoisie.getCol());
    this->addResult(coordChoisie.getRow());

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


#include "pausemenu.hpp"
#include "GameActors/game.hpp"

extern Game* global_game;

void PauseMenu::show() {
    int choix;
    std::cout << "\n=== Menu Pause ===\n";
    std::cout << "0 : Reprendre la partie\n";
    std::cout << "1 : Recommencer\n";
    std::cout << "2 : Quitter le jeu\n";
    std::cout << "Votre choix : ";
    std::cin >> choix;

    switch (choix) {
    case 0:
        std::cout << "Reprise de la partie...\n";
        break;
    case 1:
        global_game->restart();
        break;
    case 2:
        global_game->quit();
        break;
    default:
        std::cout << "Choix invalide. Reprise automatique.\n";
        break;
    }
}

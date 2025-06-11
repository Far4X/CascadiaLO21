#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <string>

class Game;

class PauseMenu {
    Game& m_game;

public:
    PauseMenu(Game& game);
    void show(); // Affiche le menu et gère les choix
};

#endif // PAUSEMENU_H

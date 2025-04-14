#include "game.hpp"
#include "../Gametools/customerror.hpp"

Game::Game(App *app, unsigned int nb_player) : m_nb_players = nb_player{
    m_app = app;
    if (app == nullptr){
        throw CustomError("No app provided for game; Shutdown", 1);
    }
}

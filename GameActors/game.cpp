#include "game.hpp"
#include "../Gametools/customerror.hpp"

Game::Game(App *app) : m_nb_players(0){
    m_app = app;
    if (app == nullptr){
        throw CustomError("No app provided for game; Shutdown", 1);
    }
}

std::string Game::getSaveString() const {
    return "";
}
void Game::play(){

}
void Game::init(){

}
void Game::getInfoConsole(){

}
void Game::getInfoGX(){

}

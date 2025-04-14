#include "game.hpp"
#include "customerror.hpp"


Game::Game(App *app) {
    m_app = app;
    if (app == nullptr){
        throw CustomError("No app provided for game; Shutdown", 1);
    }
}

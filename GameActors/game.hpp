#ifndef GAME_H
#define GAME_H
#include "app.hpp"

class Game{
    App *m_app;
public:
    Game(App *app = nullptr);
    std::string generateSaveString() const;


};

#endif // GAME_H

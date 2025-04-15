#ifndef GAME_H
#define GAME_H
#include "app.hpp"
#include "Gametools//Abstract/salvablething.hpp"

class Game : public SalvableThing {
    App *m_app;
    unsigned short m_nb_players = 0;
public:
    Game(App *app = nullptr);
    std::string getSaveString() const override;
    void play();
    void init();
    void getInfoConsole();
    void getInfoGX();
};

#endif // GAME_H

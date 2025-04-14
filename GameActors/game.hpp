#ifndef GAME_H
#define GAME_H
#include "app.hpp"
#include "Gametools//Abstract/salvablething.hpp"

class Game : public SalvableThing {
    App *m_app;
    const unsigned int m_nb_players;
public:
    Game(App *app = nullptr, unsigned int nb_player = 2);
    std::string getSaveString() const override;

};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H
#include "app.hpp"
#include "Gametools/Abstract/salvablething.hpp"
#include "Gametools/Abstract/notifiableinterface.hpp"
#include "gameactors.hpp"



class Game : public SalvableThing, public NotifiableInterface {
    App *m_app;
    unsigned short m_nb_players = 0;
    PlayerMenu* m_pm = nullptr;


public:
    Game(App *app = nullptr);
    std::string getSaveString() const override;
    void play();
    void init();
    void getInfoConsole();
    void getInfoGX();
    void notify(unsigned int code) override;
};

#endif // GAME_H

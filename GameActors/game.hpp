#ifndef GAME_H
#define GAME_H
#include "Gametools/Abstract/salvablething.hpp"
#include "Gametools/Abstract/notifiableinterface.hpp"
#include "gameactors.hpp"
#include "player.hpp"
#include <vector>

class Game : public SalvableThing, public NotifiableInterface {
    unsigned short m_nb_players = 0;
    Menu<std::string>* m_player_menu = nullptr;
    const bool m_is_console;
    std::vector<Player> m_players;

public:
    Game(const bool is_console = false);
    ~Game();
    std::string getSaveString() const override;
    void play();
    void init();
    void getInfoConsole();
    void getInfoGX();
    void notify(unsigned int code) override;
};

#endif // GAME_H

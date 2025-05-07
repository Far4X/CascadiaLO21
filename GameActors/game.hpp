#ifndef GAME_H
#define GAME_H
#include "Gametools/Abstract/salvablething.hpp"
#include "Gametools/Abstract/notifiableinterface.hpp"
#include "gameactors.hpp"
#include "GraphicalComponents/graphicalcomponents.hpp"
#include "player.hpp"
#include <vector>

enum class GameStatus {
    NotStarted,
    Running,
    Quit,
    Restart
};

class Game : public SalvableThing, public NotifiableInterface {
    unsigned short m_nb_players = 0;
    Menu<std::string>* m_player_menu = nullptr;
    Menu<std::tuple<std::string, std::string>>* m_game_menu = nullptr;

    const bool m_is_console;
    std::vector<Player*> m_players;
    GameTile** m_cards = nullptr;
    unsigned short int m_nb_cards = 0;
    GameStatus m_status = GameStatus::NotStarted;


public:
    Game(const bool is_console = false);
    ~Game();
    std::string getSaveString() const override;
    void readCards(std::string path = "tiles.cts");
    void play();
    void init();
    void getInfoConsole();
    void getInfoGX();
    GameStatus getGameStatus() const;
    void notify(unsigned int code) override;
    void restart();
    void quit();


};

#endif // GAME_H

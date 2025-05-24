#ifndef GAME_H
#define GAME_H
#include "../Gametools/Abstract/salvablething.hpp"
#include "../Gametools/Abstract/notifiableinterface.hpp"
#include "gameactors.hpp"
#include "GraphicalComponents/graphicalcomponents.hpp"
#include "player.hpp"
#include "../../scoring/scoringstrategies/tilescoringstrategy.hpp"
#include "../../scoring/scoringstrategies/wildlifescoringstrategy.hpp"
#include <QObject>

#include <vector>

enum class GameStatus {
    NotStarted,
    Running,
    Quit,
    Restart
};

class Game : public SalvableThing, public NotifiableInterface, public QObject {
    unsigned short m_nb_players = 0;
    Menu<std::string>* m_player_menu = nullptr;
    Menu<std::tuple<std::string, std::string>>* m_game_menu = nullptr;
    Menu<unsigned short int>* m_menu_token = nullptr;
    DeckTile* m_decktile = nullptr;

    const bool m_is_console;

    bool m_is_waiting_for_position = false;
    bool m_is_waiting_to_place_tile = false;
    GameTile* m_tile_to_add = nullptr;
    const WildlifeToken* m_token_to_add = nullptr;

    std::vector<Player*> m_players;
    std::vector<const WildlifeToken*> m_tokens;
    GameTile** m_cards = nullptr;
    GameTile* m_starter_cards[5][3];
    unsigned short int m_nb_cards = 0;
    GameStatus m_status = GameStatus::NotStarted;

    unsigned short int current_tour = 0;
    unsigned short int current_player = 0;
    std::vector <void *> throwaway;
    Score m_scorer;
    NotifiableInterface* const m_target;


public:
    Game(NotifiableInterface* interface, const bool is_console = false);
    ~Game();
    std::string getSaveString() const override;
    void readCards(std::string path = ":/Assets/Assets/ListTiles.lst");
    void play();
    void init();
    void getTileAndToken(unsigned short int pos_tile, unsigned short int pos_token = -1);
    //void makePlayerTurn(unsigned short int id_player, GameTile& tile, const WildlifeToken& token);
    void makePlayerTurn();
    void initPlayerboards();
    void getInfoConsole();
    void getInfoGX();
    void scoreGame();
    GameStatus getGameStatus() const;
    void readNotification(unsigned int code);
    void notifyInterface(unsigned int code) override;
    void restart();
    void quit();
    const DeckTile* getDeckTile() const {return m_decktile;};
};

#endif // GAME_H

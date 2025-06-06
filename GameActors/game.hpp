#ifndef GAME_H
#define GAME_H
#include "../Gametools/Abstract/salvablething.hpp"
#include "../Gametools/Abstract/notifiableinterface.hpp"
#include "gameactors.hpp"
#include "GraphicalComponents/graphicalcomponents.hpp"
#include "player.hpp"
#include "../../scoring/scoringstrategies/tilescoringstrategy.hpp"
#include "../../scoring/scoringstrategies/wildlifescoringstrategy.hpp"
#include "../../scoring/score.hpp"
#include <QObject>

#include <vector>

class GraphxVue;

enum class GameStatus {
    NotStarted,
    Running,
    Quit,
    Restart
};

class Game : public SalvableThing, public NotifiableInterface, public QObject {
    /*Classe qui représente le déroulement de la partie*/
    unsigned short m_extension = 0;
    std::string m_desc_cards = "AAAAA"; //Not implemented yet
    unsigned short m_nb_players = 0;
    bool m_is_console;

    Menu<std::string>* m_player_menu = nullptr; //Représente le menu sélectionneur de joueurs
    Menu<std::tuple<std::string, std::string>>* m_game_menu = nullptr;  //Représente le menu sélectionneur du jeu
    Menu<unsigned short int>* m_menu_token = nullptr; //Représente le menu utile pour choisir le token et la tuile à poser
    Menu<bool>* m_menu_validate = nullptr; //Représente le menu qui permet de valider les changements

    bool m_is_waiting_for_position = false; //Variable booléenne pour savoir si on attend une position
    bool m_is_waiting_to_place_tile = false;
    GameTile* m_tile_to_add = nullptr; //Stocke la tuile en attente
    const WildlifeToken* m_token_to_add = nullptr;
    Score m_scorer;

    std::vector<Player*> m_players;
    DeckTile* m_decktile = nullptr;
    GameStatus m_status = GameStatus::NotStarted;

    //PlayerBoard* m_board_before_change = nullptr;
    std::vector<const WildlifeToken*> m_tokens;
    GameTile** m_cards = nullptr;
    GameTile* m_starter_cards[5][3];
    unsigned short int m_nb_cards = 0;

    unsigned short int current_tour = 0;
    unsigned short int current_player = 0;
    //std::vector <void *> throwaway;
    NotifiableInterface* const m_target;
    void endTurn();
    void resurrectGame();
    void interpretString(std::string &def);
    void saveGame() const;



public:
    Game(NotifiableInterface* interface, const bool is_console = false);
    ~Game();
    std::string getSaveString() const override;
    void readCards(std::string path = ":/Assets/Assets/ListTiles.lst");
    void play();
    void init();
    void getTileAndToken(unsigned short int pos_tile, unsigned short int pos_token = -1);
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

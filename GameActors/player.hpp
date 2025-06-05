#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>

#include "../Gametools/Abstract/salvablething.hpp"
#include "../Gametools/Tiling/gametile.hpp"
#include "../Gametools/wildlifetoken.hpp"
#include "../Gametools/Abstract/playerboard.hpp"
#include "GraphicalComponents/Console/cplayerboard.hpp"
#include "GraphicalComponents/GraphX/gplayerboard.hpp"

class Player : public SalvableThing {
    friend class Game;

    std::string m_name;
    unsigned int bonusScore = 0;// "C'est le score bonus tu sais pour celui qui est premier" Zakariae, 3 juin 2025 "C'est bien, c'est assez descriptif"
    const unsigned int m_id;
    unsigned int m_score = 0;
    static unsigned int nb_players;
    //std::vector<GameTile*> m_tiles;
    //std::vector<WildlifeToken*> m_tokens;
    PlayerBoard* m_board = nullptr;
    unsigned short int m_nb_nature_token = 0;
    std::vector<double> m_tiles_scores;
    std::vector<double> m_tokens_scores;
    Player(const std::string& def, const bool is_console, NotifiableInterface* tar_board); //Used to ressucite after reloading game


public:
    Player(const std::string& name, PlayerBoard* bd);
    Player(const Player&) = default;

    static int getNbPlayers() { return nb_players;}
    const std::string getName() const {return m_name;}
    unsigned int getId() const {return m_id;}
    unsigned int getScore() const {return m_score;}
    PlayerBoard* getBoard() const {return m_board;}
    unsigned short int getNbNatureToken() const {return m_nb_nature_token;};
    void addNatureToken() {m_nb_nature_token++;};
    bool removeNatureToken() {if (m_nb_nature_token > 0){m_nb_nature_token--; return true;} return false;}
    std::vector<double> getTilesScores() const { return m_tiles_scores; }
    std::vector<double> getTokensScores() const { return m_tokens_scores; }

    void setName(const std::string& name);
    void addScore(unsigned int points);
    void setTilesScores(const std::vector<double>& scores);
    void setTokensScores(const std::vector<double>& scores);

    void addTile(GameTile* tile);
    void addToken(WildlifeToken* token);
    void setBoard(PlayerBoard* board);
    ~Player();


    std::string getSaveString() const override;

    };

#endif // PLAYER_HPP

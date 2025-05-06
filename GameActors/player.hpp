#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

#include "Gametools/Abstract/salvablething.hpp"
#include "Gametools/Tiling/gametile.hpp"
#include "../Gametools/wildlifetoken.hpp"
#include "Gametools/Abstract/playerboard.hpp"

class Player : public SalvableThing {
    friend class Game;

    std::string m_name;
    const unsigned int m_id;
    unsigned int m_score = 0;
    static unsigned int nb_players;

    std::vector<GameTile*> m_tiles;
    std::vector<WildlifeToken*> m_tokens;
    PlayerBoard* m_board;

    Player(const std::string& name);

public:
    Player(const Player&) = default;
    static int getNbPlayers() { return nb_players;}
    const std::string getName() const {return m_name;}
    unsigned int getId() const {return m_id;}
    unsigned int getScore() const {return m_score;}
    PlayerBoard* getBoard() const {return m_board;}

    void setName(const std::string& name);
    void addScore(unsigned int points);

    void addTile(GameTile* tile);
    void addToken(WildlifeToken* token);
    void setBoard(PlayerBoard* board);
    ~Player();


    std::string getSaveString() const override;


    };

#endif // PLAYER_HPP

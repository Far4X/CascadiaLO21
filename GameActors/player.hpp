#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

#include "Gametools/Abstract/salvablething.hpp"

class WildlifeToken;
class GameTile;

class Player : public SalvableThing {
    friend class Game;

    std::string m_name;
    const unsigned int m_id;
    unsigned int m_score = 0;
    static unsigned int nb_players;

    std::vector<GameTile*> m_tiles;
    std::vector<WildlifeToken*> m_tokens;

    // Constructeur
    Player(const std::string& name);

    // Destructeur
    ~Player();

    Player(const  Player&) = delete;
    Player& operator=(const Player&) = delete;

public:
    // Accesseurs en lecture
    static int getNbPlayers() { return nb_players;}
    const std::string getName() const {return m_name;}
    unsigned int getId() const {return m_id;}
    unsigned int getScore() const {return m_score;}

    // Accesseurs en écriture
    void setName(const std::string& name);
    void addScore(unsigned int points);

    void addTile(GameTile* tile);
    void addToken(WildlifeToken* token);


    };

#endif // PLAYER_HPP

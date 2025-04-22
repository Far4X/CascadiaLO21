#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

using namespace std;

class Player{
    friend class Game;

    std::string m_name;
    const unsigned int m_id;
    unsigned int m_score = 0;
    static unsigned int nb_players;

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


    };

#endif // PLAYER_HPP

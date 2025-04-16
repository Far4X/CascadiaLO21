#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

class Player{
    std::string m_name;
    int m_id;
    static int nb;
public:
    Player(std::string name);
};

#endif // PLAYER_HPP

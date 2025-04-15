#include "player.hpp"

int Player::nb = 0;

Player::Player(std::string name) {
    m_name = name;
    m_id = Player::nb;
    Player::nb++;
}

#include "player.hpp"

unsigned int Player::nb_players = 0;

Player::Player(const std::string& name) : m_name(name), m_id(++nb_players){

}


Player::~Player() {
    Player::nb_players--;
    delete m_board;
    m_board = nullptr;
}


void Player::setName(const std::string& name) {
    m_name = name;
}

void Player::addScore(unsigned int points) {
    m_score += points;
}

void Player::addTile(GameTile* tile){
    m_tiles.push_back(tile);
};
void Player::addToken(WildlifeToken* token){
    m_tokens.push_back(token);
};

void Player::setBoard(PlayerBoard* board){
    m_board = board;
};

std::string Player::getSaveString() const{
    return "";
}

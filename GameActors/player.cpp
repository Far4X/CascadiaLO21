#include "player.hpp"
#include <iostream>

unsigned int Player::nb_players = 0;

Player::Player(const std::string& name, PlayerBoard* bd) : m_name(name), m_id(++nb_players), m_tiles_scores(5, 0.0), m_tokens_scores(5, 0.0) {
    this->setBoard(bd);
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

void Player::setTilesScores(const std::vector<double>& scores) {
    m_tiles_scores = scores;
}

void Player::setTokensScores(const std::vector<double>& scores) {
    m_tokens_scores = scores;
}

/*void Player::addTile(GameTile* tile){
    m_tiles.push_back(tile);
};
void Player::addToken(WildlifeToken* token){
    m_tokens.push_back(token);
};*/

void Player::setBoard(PlayerBoard* board){
    m_board = board;
};

std::string Player::getSaveString() const{
    //Permet de pouvoir sauvegarder un joueur
    std::string rt = "{";
    rt += m_name;
    rt += ";" + std::to_string(m_nb_nature_token) + ";" + m_board->getSaveString()  + ";}";
    return rt;
}

Player::Player(const std::string& def, const bool is_console, NotifiableInterface* tar_board) : m_id(++nb_players), m_tiles_scores(5, 0.0), m_tokens_scores(5, 0.0){
    //Permet de pouvoir ressusuter un joueur grâce à sa trace laissée dans l'histoire
    std::vector<std::string> params = SalvableThing::separateParams(def);
    for (const auto &a : params){
        std::cout << a << std::endl;
    }
    m_name = params[0];
    m_nb_nature_token = static_cast<unsigned int>(SalvableThing::stringToInt(params[1]));
    if (is_console){
        m_board = new CPlayerBoard(tar_board, params[2]);
    }
    else {
        m_board = new GPlayerBoard(tar_board, params[2]);
    }
}

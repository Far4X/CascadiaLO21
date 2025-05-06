#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include <iostream>
#include <fstream>

Game::Game(const bool is_console) : m_nb_players(0), m_is_console(is_console){
    //readCards();
    m_cards = new GameTile*;
    *m_cards = new GameTile(0, "112233213");
    char** repr;
    repr = getRepresentation(**m_cards);
    for (int i = 0; i < 2*5 +1; i++){
        for (int j = 0; j < 4*5; j++){
            std::cout << repr[i][j];
        }
        std::cout << std::endl;
    }
}

Game::~Game(){
    std::cout << "Game deleted" << std::endl;
    for (int i = 0; i < m_nb_cards; i++){
        delete m_cards[i];
    }
    delete[] m_cards;
    delete m_player_menu;
}

GameStatus Game::getGameStatus() const { return m_status; }

std::string Game::getSaveString() const {
    return "";
}
void Game::play(){
    m_status = GameStatus::Running;
    
    if (m_is_console){
        m_game_menu = new CGameMenu(this);
    }
    else {
        m_game_menu = new GGameMenu(this);
    }
    m_game_menu->show();
}
void Game::init(){

}
void Game::getInfoConsole(){

}
void Game::getInfoGX(){

}

void Game::notify(unsigned int code){
    if (code == 1){
        Player *pl = nullptr;
        for (Menu<std::string>::Iterator it = m_player_menu->getIterator(); !it.isDone(); it++){
            std::cout << it.getValue() << std::endl;
            pl = new Player(it.getValue());
            m_players.push_back(pl);
            PlayerBoard* bd;
            if (m_is_console){
                bd = new CPlayerBoard();
            }
            else {
                bd = new GPlayerBoard();
            }
            m_players.back()->setBoard(bd);
            std::cout << m_players.back()->getName() << std::endl;
        }
        std::cout << "Show board" << std::endl;
        m_players[0]->getBoard()->show();
    }
    if (code == 2){
        if (m_is_console){
            m_player_menu = new CPlayerMenu(this);
        }
        else {
            m_player_menu = new GPlayerMenu(this);
        }
        m_player_menu->show();
    }
}

void Game::readCards(std::string path){
    std::ifstream istream(path);
    char chr;
    int tmp_nb = 0;
    unsigned short int current_m_tiles = 0;
    std::string desc_tile;
    while (istream.get(chr)){
        if (m_nb_cards == 0){
            if (chr >= '0' && chr <= '9'){
                tmp_nb *= 10;
                tmp_nb += chr - '0';
            }
            else if (chr == ';'){
                m_nb_cards = tmp_nb;
                m_cards = new GameTile*[m_nb_cards];
            }
        }
        else {
            if (chr == ';'){
                m_cards[current_m_tiles] = new GameTile(current_m_tiles, desc_tile);
                current_m_tiles++;
            }
            else {
                desc_tile += std::to_string(chr);
            }
        }
    }

}

void Game::quit(){
    std::cout<<"Partie terminée"<<std::endl;
    m_status = GameStatus::Quit;

}

void Game::restart(){
    std::cout<<"Redemarrage d'une nouvelle partie..."<<std::endl;
    delete m_player_menu;
    delete m_game_menu;
    m_player_menu = nullptr;
    m_game_menu = nullptr;
    m_players.clear();
    m_nb_players = 0;
    m_status = GameStatus::Restart;

}

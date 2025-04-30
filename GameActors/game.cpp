#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include <iostream>
#include <fstream>

Game::Game(const bool is_console) : m_nb_players(0), m_is_console(is_console){

}

Game::~Game(){
    std::cout << "Game deleted" << std::endl;
    delete m_player_menu;
}

std::string Game::getSaveString() const {
    return "";
}
void Game::play(){


    if (m_is_console){
        m_player_menu = new CPlayerMenu();
    }
    else {
        m_player_menu = new GPlayerMenu(this);
    }
    m_player_menu->show();

}
void Game::init(){

}
void Game::getInfoConsole(){

}
void Game::getInfoGX(){

}

void Game::notify(unsigned int code){
    if (code == 1){
        for (Menu<std::string>::Iterator it = m_player_menu->getIterator(); !it.isDone(); it++){
            m_players.push_back(Player(it.getValue()));
        }
    }
}

void Game::readCards(std::string path){
    std::ifstream istream(path);
    char chr;
    int tmp_nb = 0;
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
    }

}


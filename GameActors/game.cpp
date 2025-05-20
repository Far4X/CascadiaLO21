#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include <iostream>
#include <fstream>
#include <random>


Game::Game(const bool is_console) : m_nb_players(0), m_is_console(is_console){
    std::srand(std::time(0)); // debug
    m_cards = new GameTile*;
    readCards();
}

Game::~Game(){
    std::cout << "Game deleted" << std::endl;
    for (int i = 0; i < m_nb_cards; i++){
        delete m_cards[i];
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 3; j++){
            delete m_starter_cards[i][j];
        }
    }
    delete[] m_cards;
    delete m_player_menu;
}

GameStatus Game::getGameStatus() const {
    return m_status;
}

std::string Game::getSaveString() const {
    return "";
}
void Game::init(){
    m_status = GameStatus::Running;

    if (m_is_console){
        m_game_menu = new CGameMenu(this);
    }
    else {
        m_game_menu = new GGameMenu(this);
    }
    m_game_menu->show();
}

void Game::play(){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < m_nb_players; j++){
            makePlayerTurn(j);
        }
    }
}

void Game::getInfoConsole(){

}

void Game::getInfoGX(){

}

void Game::initPlayerboards(){
    std::cout << "Init playerboard : " << m_nb_players << std::endl;

    m_starter_cards[0][0] = new GameTile(1000, "2223333245");
    m_starter_cards[0][1] = new GameTile(1001, "55555515");
    m_starter_cards[0][2] = new GameTile(1002, "444111213");

    m_starter_cards[1][0] = new GameTile(1003, "3331113423");
    m_starter_cards[1][1] = new GameTile(1004, "22222214");
    m_starter_cards[1][2] = new GameTile(1005, "444555215");

    m_starter_cards[2][0] = new GameTile(1006, "1112223354");
    m_starter_cards[2][1] = new GameTile(1007, "44444411");
    m_starter_cards[2][2] = new GameTile(1008, "333555212");

    m_starter_cards[3][0] = new GameTile(1009, "5551113123");
    m_starter_cards[3][1] = new GameTile(1010, "33333312");
    m_starter_cards[3][2] = new GameTile(1011, "444222245");

    m_starter_cards[4][0] = new GameTile(1012, "4443333134");
    m_starter_cards[4][1] = new GameTile(1013, "11111113");
    m_starter_cards[4][2] = new GameTile(1014, "555222252");

    for (int i = 0; i < 5; i ++){
        m_starter_cards[i][0]->Rotate(Trigonometric);
        m_starter_cards[i][0]->setPos(-1, 2);
        m_starter_cards[i][1]->setPos(0, 0);
        m_starter_cards[i][2]->setPos(0, 1);

    }


    std::random_device rd;
    std::mt19937 rng(rd());
    for (int i = 0; i < m_nb_players; i++){
        std::uniform_int_distribution<int> uni(0,4-i);
        int index = uni(rng);
        GameTile* tmp = nullptr;
        for (int j = 0; j < 3; j++){
            m_players[i]->getBoard()->addTile(*(m_starter_cards[index][j]));
            tmp = m_starter_cards[index][j];
            m_starter_cards[index][j] = m_starter_cards[4-i][j];
            m_starter_cards[4-i][j] = tmp;

        }
        //m_players[i]->getBoard()->show();
    }
}

void Game::getTileAndToken(){

}

void Game::makePlayerTurn(unsigned short int id_player, GameTile& tile, const WildlifeToken& token){
    m_decktile->show();
    if (m_players[id_player]->getNbNatureToken() > 0){

    }

    HexCell target;
    bool cnt = true;
    while (cnt){
        m_players[id_player]->getBoard()->show();
        target = HexCell(m_players[id_player]->getBoard()->getPointedCell());
        //std::cout << "Hexcell pos : " << target.getQ() << ", " << target.getR() << std::endl;
        if ((m_players[id_player]->getBoard()->hasNeighbour(target)) && m_players[id_player]->getBoard()->getTile(target.getQ(), target.getR()) == nullptr){
            cnt = false;
        }
    }
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
        m_nb_players = m_players.size();
        initPlayerboards();

    }
    if (code == 2){
        if (m_is_console){
            m_player_menu = new CPlayerMenu(this);
            m_decktile = &CDeckTile::getInstance();
        }
        else {
            m_player_menu = new GPlayerMenu(this);
        }
        m_player_menu->show();
    }
    play();
}

void Game::readCards(std::string path){
    if (path == ""){
        // debug
        m_cards = new GameTile*[9];
        m_nb_cards = 9;
        m_cards[0] = new GameTile(1, "1111110");
        m_cards[1] = new GameTile(2, "2222220");
        m_cards[2] = new GameTile(3, "3333330");
        m_cards[3] = new GameTile(4, "4444440");
        m_cards[4] = new GameTile(5, "5555550");
        m_cards[5] = new GameTile(6, "1112220");
        m_cards[6] = new GameTile(7, "3332220");
        m_cards[7] = new GameTile(8, "4442220");
        m_cards[8] = new GameTile(9, "5552220");

    }
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

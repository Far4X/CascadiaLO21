#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include "scoring/scoreutils.hpp"
#include <iostream>
#include <fstream>

Game::Game(const bool is_console) : m_nb_players(0), m_is_console(is_console) {
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

void Game::scoreGame() {
    // à rajouter
    /* if (m_status != Finished) {
     * throw "Cannot score an unfinished game";
    */
    for (size_t i = 0; i < m_nb_players; i++) {  // boucle joueurs
        auto board = m_players[i]->getBoard();

        // PARTIE TUILES
        TileScoringStrategy tile_strategy;
        auto tile_scores = m_scorer.obtainScore(*board, tile_strategy);
        m_players[i]->setTilesScores(tile_scores);

        // PARTIE JETONS
        /* Pour chaque carte de marquage, on va calculer le score et append ce score au vecteur wildlife_scores */
        const auto& cards = m_scorer.getScoringCards();
        std::vector<double> wildlife_scores(cards.size());
        for (size_t j = 0; j < cards.size(); j++) {
            m_scorer.setStrategy(j);
            wildlife_scores[j] = m_scorer.obtainScore(*board)[0];  // on copie la premiere valeur dans le vecteur de scores retourné par computeScore (le seul score)
            // c'est un vecteur de double et pas un double normal parce que ça permet d'unifier la logique avec celle des tuiles
        }
        m_players[i]->setTokensScores(wildlife_scores);
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
        std::cout << "Show board" << std::endl;
        m_players[0]->getBoard()->show();
    }
    if (code == 2){
        for (Menu<std::tuple<std::string,std::string>>::Iterator it = m_game_menu->getIterator(); !it.isDone(); it++) {
            auto tup = it.getValue();
            const std::string& key = std::get<0>(tup);
            const std::string& value = std::get<1>(tup);
            if (key == "Use cards") {
                m_scorer.configureCards(value);
            }
        }
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

#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include "scoring/scoreutils.hpp"
#include <iostream>
#include <random>
#include <QFile>
#include <QTextStream>


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

    for (size_t i = 0; i < throwaway.size(); i++){
        delete throwaway[i];
    }
    for (size_t i = 0; i < m_tokens.size(); i++){
        delete m_tokens[i];
    }
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
            makePlayerTurn();
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
    }
}

void Game::getTileAndToken(unsigned short int pos_tile, unsigned short int pos_token){
    m_is_waiting_for_position = true;
    m_is_waiting_to_place_tile = true;
    std::cout << "Pos tile : " << pos_tile << ", pos token : " << pos_token << std::endl;

    std::tuple<GameTile*, const WildlifeToken*> tmp = m_decktile->getCouple(pos_tile, pos_token);
    m_tile_to_add = std::get<0>(tmp);
    m_token_to_add = std::get<1>(tmp);
    std::cout << "Token : " << m_token_to_add << std::endl;
    std::cout << "Tile : " << m_tile_to_add << std::endl;
}

void Game::makePlayerTurn(){
    if (m_is_console){
        std::cout << "----- \nTour de " << m_players[current_player]->getName() << std::endl;
        m_menu_token = new CTokenMenu(this, m_decktile, m_players[current_player]->getNbNatureToken());
    }
    else {
        m_menu_token = new GTokenMenu(this, m_decktile, m_players[current_player]->getNbNatureToken());
    }

    m_players[current_player]->getBoard()->show();
    return m_menu_token->show();

    /*HexCell target;
    bool cnt = true;
    while (cnt){
        m_players[id_player]->getBoard()->show();
        target = HexCell(m_players[id_player]->getBoard()->getPointedCell());
        //std::cout << "Hexcell pos : " << target.getQ() << ", " << target.getR() << std::endl;
        if ((m_players[id_player]->getBoard()->hasNeighbour(target)) && m_players[id_player]->getBoard()->getTile(target.getQ(), target.getR()) == nullptr){
            cnt = false;
        }
    }*/
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
                bd = new CPlayerBoard(this);
            }
            else {
                bd = new GPlayerBoard(this);
            }
            m_players.back()->setBoard(bd);
            std::cout << m_players.back()->getName() << std::endl;
        }
        m_nb_players = m_players.size();
        initPlayerboards();
        return makePlayerTurn();
    }

    if (code == 2){
        for (Menu<std::tuple<std::string,std::string>>::Iterator it = m_game_menu->getIterator(); !it.isDone(); it++) {
            auto tup = it.getValue();
            const std::string& key = std::get<0>(tup);
            const std::string& value = std::get<1>(tup);
            if (key == "Use cards") {
                m_scorer.configureCards(value);
                std::cout << "cartes configurees avec succes";
            }
            if (key == "Test scroring") {
                readCards();
                scoreGame();
            }
        }
        if (m_is_console){
            m_player_menu = new CPlayerMenu(this);
            m_decktile = &CDeckTile::getInstance();
        }
        else {
            m_player_menu = new GPlayerMenu(this);
            m_decktile = &GDeckTile::getInstance();
        }

        for (size_t i = 0; i < m_tokens.size(); i++){
            m_decktile->addToken(m_tokens[i]);
        }
        for (int i = 0; i < m_nb_cards; i++){
            m_decktile->addTile(m_cards[i]);
        }
        m_decktile->fillPlate();
        m_player_menu->show();
        return play();
    }

    if (code == 3){
        if (m_menu_token == nullptr){
            throw CustomError("Menu token not initialized", 1);
        }
        std::cout << "Game notified with code 3" << std::endl;
        std::vector<unsigned short int> params;
        for (Menu<unsigned short int>::Iterator it = m_menu_token->getIterator(); !it.isDone(); it++){
            params.push_back(it.getValue());
        }
        delete m_menu_token;
        //throwaway.push_back(m_menu_token);
        m_menu_token = nullptr;
        if (params.size() == 2){
            getTileAndToken(params[0], params[1]);
        }
        else {
            getTileAndToken(params[0]);
        }

        m_players[current_player]->getBoard()->resetPointedCell();
        m_is_waiting_for_position = true;
        m_is_waiting_to_place_tile = true;
        return m_players[current_player]->getBoard()->show();
    }

    if (code == 4){
        if (m_is_waiting_for_position == false){
            return;
        }
        if (m_is_waiting_to_place_tile){
            HexCell target = HexCell(m_players[current_player]->getBoard()->getPointedCell());
            if ((m_players[current_player]->getBoard()->hasNeighbour(target)) && m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR()) == nullptr){
                m_is_waiting_to_place_tile = false;
                m_tile_to_add->setPos(target.getQ(), target.getR());
                unsigned short int rotation = 0;

                if (m_is_console){
                    std::cout << "Indiquez de combien de 1/6 de tour vous voulez tourner la tuile, dans le sens trigo : (0 à 5)";
                    std::string result;
                    std::cin >> result;
                    if (result.size() == 1){
                        if (result[0] < '6' && result[0] >= '0'){
                            rotation = result[0] - '0';
                        }
                    }
                    std::cout << "Merci de choisir l'emplacement pour le pion faune : ";
                }

                for (int i = 0; i < rotation; i++){
                    m_tile_to_add->Rotate(Trigonometric);
                }

                m_players[current_player]->getBoard()->addTile(*m_tile_to_add);
                m_tile_to_add = nullptr;
                return m_players[current_player]->getBoard()->show();
            }
            else {
                HexCell target = HexCell(m_players[current_player]->getBoard()->getPointedCell());
                if ((m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR()) != nullptr) && (m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR())->getToken() == nullptr)){
                    // Check if token well in list !!!!!!!!

                    m_is_waiting_for_position = false;
                    m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR())->setWildLifeToken(m_token_to_add);
                    if (m_is_console){
                        std::cout << "Le token a bien été placé." << std::endl;
                    }
                    current_player++;
                    if (current_player == m_nb_players){
                        current_player = 0;
                        current_tour++;
                        if (current_tour == 20){
                            return scoreGame();
                        }
                        return makePlayerTurn();
                    }
                }
                else {

                }
            }
        }
        else {
            std::cout << "Here cap" << std::endl;
        }
    }
}

void Game::readCards(std::string path){
    for (int i = 0; i < 30; i++){
        m_tokens.push_back(new WildlifeToken(Fox));
        m_tokens.push_back(new WildlifeToken(Bear));
        m_tokens.push_back(new WildlifeToken(Elk));
        m_tokens.push_back(new WildlifeToken(Hawk));
        m_tokens.push_back(new WildlifeToken(Salmon));
    }

    if (path == ""){
        // debug
        m_cards = new GameTile*[9];
        m_nb_cards = 9;
        m_cards[0] = new GameTile(1, "11111111");
        m_cards[1] = new GameTile(2, "222222212");
        m_cards[2] = new GameTile(3, "33333313");
        m_cards[3] = new GameTile(4, "44444414");
        m_cards[4] = new GameTile(5, "55555515");
        m_cards[5] = new GameTile(6, "111222234");
        m_cards[6] = new GameTile(7, "3332223213");
        m_cards[7] = new GameTile(8, "444222215");
        m_cards[8] = new GameTile(9, "5552223214");

        return;
    }

    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CustomError("Fnf", 800);
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QStringList parts = content.split(';', Qt::SkipEmptyParts);
    if (parts.isEmpty())
        return;

    m_nb_cards = parts[0].toInt();
    m_cards = new GameTile*[m_nb_cards];

    for (int i = 1; i <= m_nb_cards && i < parts.size(); ++i) {
        m_cards[i - 1] = new GameTile(i, parts[i].toStdString());
    }


    /*char chr;
    int tmp_nb = 0;
    unsigned short int current_m_tiles = 0;
    std::string desc_tile;
    while (istream.get(chr)){
        std::cout << "Here" << std::endl;

        if (m_nb_cards == 0){
            if (chr >= '0' && chr <= '9'){
                tmp_nb *= 10;
                tmp_nb += chr - '0';
            }
            else if (chr == ';'){
                std::cout << "Nb chr : " << tmp_nb << std::endl;
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
    }*/
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

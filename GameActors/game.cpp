#include "game.hpp"
#include "../Gametools/customerror.hpp"
#include "GameActors/GraphicalComponents/GraphX/graphxvue.hpp"
#include "scoring/scoreutils.hpp"
#include <iostream>
#include <random>
#include <QFile>
#include <QTextStream>

#define NB_TYPE_TILES 5

Game::Game(NotifiableInterface* interface, const bool is_console) : m_nb_players(0), m_is_console(is_console), m_target(interface){
    std::srand(std::time(0)); // debug
    m_cards = new GameTile*;
    readCards();
    if (m_is_console){
        m_message_box = new CMessageBox();
    }
    else {
        m_message_box = new GMessageBox();

    }
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

    /*for (size_t i = 0; i < throwaway.size(); i++){
        delete throwaway[i];
    }*/
    for (size_t i = 0; i < m_tokens.size(); i++){
        delete m_tokens[i];
    }
    delete m_message_box;
    m_message_box = nullptr;
}

GameStatus Game::getGameStatus() const {
    return m_status;
}

std::string Game::getSaveString() const {
    std::string rt = "{";
    rt += std::to_string(m_nb_players);
    rt += ";" + std::to_string(m_extension) + ";" + m_desc_cards + ";" + std::to_string(current_tour) + ";" + std::to_string(m_is_console) + ";";
    for (size_t i = 0; i < m_nb_players; i++){
        rt += m_players[i]->getSaveString();
        rt += ";";
    }
    rt += m_decktile->getSaveString();
    rt += ";}";
    return rt;
}

void Game::saveGame() const{
    QFile file(QString::fromStdString("cache.svp"));

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        std::cout << "Bf entering" << std::endl;
        out <<QString::fromStdString(getSaveString());
        std::cout << "After" << std::endl;
        file.close();
    }
    else {
        std::cout << "Erreur lors de l'ouverture du fichier :" << file.errorString().toStdString();
    }
}


void Game::interpretString(std::string &def){
    std::vector<std::string> params = SalvableThing::separateParams(def);
    m_nb_players = SalvableThing::stringToInt(params[0]);
    std::cout << "NB : " << m_nb_players << std::endl;
    m_extension = SalvableThing::stringToInt(params[1]);
    m_desc_cards = params[2];
    current_tour = SalvableThing::stringToInt(params[3]);
    m_is_console = static_cast<bool>(SalvableThing::stringToInt(params[4]));
    for (int i = 0; i < m_nb_players; i++){
        m_players.push_back(new Player(params[5+i], m_is_console, this));
    }
    if (m_is_console){
        m_decktile = &CDeckTile::getInstance();
    }
    else {
        m_decktile = &GDeckTile::getInstance();
    }
    for (size_t i = 0; i < params.size(); i++){
    }
    m_decktile->reinterpetString(params.back());

}

void Game::resurrectGame(){
    QFile file(QString::fromStdString("cache.svp"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CustomError("Fnf", 800);
        return;
    }

    QTextStream in(&file);
    std::string content = in.readAll().toStdString();
    std::cout << content << std::endl;
    file.close();
    interpretString(content);

    std::vector<GameTile*> m_available_tiles;
    std::vector<const WildlifeToken*> m_available_tokens;
    std::cout << "0" << std::endl;

    for (size_t i = 0; i < m_nb_cards; i++){
        m_available_tiles.push_back(m_cards[i]);
    }
    for (size_t i = 0; i < 5; i++){
        for (size_t j = 0; j < 3; j++){
            m_available_tiles.push_back(m_starter_cards[i][j]);
        }
    }
    for (size_t i = 0; i < m_tokens.size(); i++){
        m_available_tokens.push_back(m_tokens[i]);
    }

    for (size_t i = 0; i < m_players.size(); i++){
        std::tuple<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int> params; // Used when ressucite. Store cards with id, posx, posy, rotation, token
        while (!m_players[i]->getBoard()->hasAllCards()){
            params = m_players[i]->getBoard()->getNextNeededCard();
            for (size_t j = 0; j < m_available_tiles.size(); j++){
                //std::cout << "Scanned : " << m_available_tiles[j]->getId() << std::endl;;
                if (m_available_tiles[j]->getId() == std::get<0>(params)){
                    HexCell pos = PlayerBoard::offsetToAxial(HexCell::Offset(std::get<1>(params), std::get<2>(params)));
                    m_available_tiles[j]->setPos(pos.getQ(), pos.getR());
                    /*for (unsigned int k = 0; k < std::get<3>(params); k++){
                        std::cout << "R" << std::endl;
                        m_available_tiles[j]->Rotate();
                    }*/
                    while (m_available_tiles[j]->getRotation() != std::get<3>(params)){
                        m_available_tiles[j]->Rotate();
                    }
                    for (unsigned int k = 0; k < m_available_tokens.size(); k++){
                        //std::cout << static_cast<unsigned int>(m_available_tokens[i]->getWildlifeType()) << ", " << std::get<4>(params) << std::endl;
                        if (static_cast<unsigned int>(m_available_tokens[k]->getWildlifeType()) == std::get<4>(params)){
                            m_available_tiles[j]->setWildLifeToken(m_available_tokens[k]);
                            m_available_tokens.erase(m_available_tokens.begin() + k);
                            k = m_available_tokens.size();
                        }
                    }
                    m_players[i]->getBoard()->addTile(*m_available_tiles[j]);
                    m_available_tiles.erase(m_available_tiles.begin() + j);
                    j = m_available_tiles.size();
                }
            }
        }
    }

    std::vector<unsigned short int> things_to_add_to_decktile = m_decktile->getCardsToAdd();
    for (size_t i = 0; i < 4; i ++) {
        for (size_t j = 0; j < m_available_tiles.size(); j++){
            if (m_available_tiles[j]->getId() == things_to_add_to_decktile[i]){
                m_decktile->m_tiles[i] = m_available_tiles[j];
                m_available_tiles.erase(m_available_tiles.begin() + j);
                j = m_available_tiles.size();
            }
        }
    }
    things_to_add_to_decktile = m_decktile->getTokensToAdd();
    for (size_t i = 0; i < 4; i ++) {
        for (size_t j = 0; j < m_available_tokens.size(); j++){
            if (static_cast<unsigned short int>(m_available_tokens[j]->getWildlifeType())== things_to_add_to_decktile[i]){
                m_decktile->m_displayed_tokens[i] = m_available_tokens[j];
                m_available_tokens.erase(m_available_tokens.begin() + j);
                j = m_available_tokens.size();
            }
        }
    }

    for (size_t i = 0; i < m_available_tokens.size(); i ++){
        m_decktile->addToken(m_available_tokens[i]);
    }
    for (size_t i = 0; i < m_available_tiles.size(); i++){
        m_decktile->addTile(m_available_tiles[i]);
    }
    makePlayerTurn();
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
    for (int i = 0; i < MAX_TURN; i++){
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
    std::cout << "Token : " << m_token_to_add->getWildlifeType() << std::endl;
    std::cout << "Tile : " << m_tile_to_add << std::endl;
}

void Game::makePlayerTurn(){
    if (current_tour >= MAX_TURN){
        scoreGame();
    }
    m_message_box->addMessage( "----- \nTour de " + m_players[current_player]->getName(), 1, 0);
    // m_message_box->show();
    std::cout << "----- \nTour de " << m_players[current_player]->getName()<< " -- Tour : " << current_tour << std::endl;

    if (m_is_console){
        m_menu_token = new CTokenMenu(this, m_decktile, m_players[current_player]);
        m_players[current_player]->getBoard()->show();
    }
    else {
        GraphXVue::instance()->show(current_player); // Update l'affichage
        GTokenMenu* gMenu = new GTokenMenu(this, m_decktile, m_players[current_player]);
        m_menu_token = gMenu;
        GraphXVue::instance()->addMenu(gMenu);

    }
    return m_menu_token->show();
}


void Game::scoreGame() {
    class maxScore final{
        std::vector<unsigned int> fst_players; //First players
        std::vector<unsigned int> snd_players; //Second ones
        unsigned int max_val = 0;
        unsigned int snd_val = 0;
    public :
        maxScore() = default;
        ~maxScore() = default;
        const std::vector<unsigned int>& getFirsts() const {return fst_players;}
        const std::vector<unsigned int>& getSeconds() const {return snd_players;}
        void considerateScore(const unsigned int &val, const unsigned int &pl){
            if (val > max_val){
                snd_players = fst_players; snd_val = max_val;
                fst_players = {}; fst_players.push_back(pl); max_val = val; return;
            }
            if (val == max_val){
                fst_players.push_back(pl); return;
            }
            if (val > snd_val){
                snd_players = {}; snd_players.push_back(pl); snd_val = val; return;
            }
            if (val == snd_val){
                snd_players.push_back(pl);
            }
        }
    };

    maxScore* tab_max_scores = new maxScore[NB_TYPE_TILES];

    for (size_t i = 0; i < m_nb_players; i++) {  // boucle joueurs
        auto board = m_players[i]->getBoard();

        // PARTIE TUILES
        TileScoringStrategy tile_strategy;
        std::vector<double> tile_scores = m_scorer.obtainScore(*board, tile_strategy);
        m_players[i]->setTilesScores(tile_scores);

        // PARTIE VARIANTES
        // std::cout << "cards : " << m_desc_cards << " size :" << m_desc_cards.size() << std::endl;
        if (m_desc_cards.size() == 1) {
            VariantScoringStrategy variant_strategy(Family);
            if (m_desc_cards == "I" || m_desc_cards == "i") {
                VariantScoringStrategy variant_strategy(Intermediate);
            }
            std::vector<double> variant_scores = m_scorer.obtainScore(*board, variant_strategy);
            m_players[i]->setTokensScores(variant_scores);
        }

        // PARTIE JETONS
        /* Pour chaque carte de marquage, on va calculer le score et append ce score au vecteur wildlife_scores */
        else {
            const auto& cards = m_scorer.getScoringCards();
            std::vector<double> wildlife_scores(cards.size());
            for (size_t j = 0; j < cards.size(); j++) {
                m_scorer.setStrategy(j);
                wildlife_scores[j] = m_scorer.obtainScore(*board)[0];  // on copie la premiere valeur dans le vecteur de scores retourné par computeScore (le seul score)
                // c'est un vecteur de double et pas un double normal parce que ça permet d'unifier la logique avec celle des tuiles
            }
            m_players[i]->setTokensScores(wildlife_scores);
        }

        int total_score = 0;
        for (int j = 0; j < 5; j++) {
            total_score += m_players[i]->getTilesScores()[j] + m_players[i]->getTokensScores()[j];
        }
        total_score += m_players[i]->getNbNatureToken();
        m_players[i]->setScore(total_score);

        std::vector<double> ti_scores = m_players[i]->getTilesScores();
        std::vector<double> to_scores = m_players[i]->getTokensScores();
        int nb_nature_tokens = m_players[i]->getNbNatureToken();

        std::cout << "Player " << i << ": " << std::endl;
        std::cout << "Bear:   " << to_scores[0] << std::endl;
        std::cout << "Elk: " << to_scores[1] << std::endl;
        std::cout << "Hawk:   " << to_scores[2] << std::endl;
        std::cout << "Fox:    " << to_scores[3] << std::endl;
        std::cout << "Salmon:    " << to_scores[4] << std::endl;

        std::cout << "Forest:   " << ti_scores[0] << std::endl;
        std::cout << "Wetland:  " << ti_scores[1] << std::endl;
        std::cout << "River:    " << ti_scores[2] << std::endl;
        std::cout << "Mountain: " << ti_scores[3] << std::endl;
        std::cout << "Prairie:  " << ti_scores[4] << std::endl;

        std::cout << "Nature token bonus: " << nb_nature_tokens << std::endl;

        for (size_t j = 0; j < ti_scores.size(); j++){
            tab_max_scores[j].considerateScore(ti_scores[j], i);
        }
    }

    for (unsigned short i = 0; i < NB_TYPE_TILES; i++){
        unsigned int nb_firsts = tab_max_scores[i].getFirsts().size();
        switch (nb_firsts) {
        case 0 :
            throw CustomError("Nobody wins. There is no war, so there is an error", 89);
            break;
        case 1:
            m_players[tab_max_scores[i].getFirsts()[0]]->addScore(3);
            for (unsigned int pl : tab_max_scores[i].getSeconds()){
                m_players[pl]->addScore(1);
            }
            break;
        case 2:
            for (unsigned int pl : tab_max_scores[i].getFirsts()){
                m_players[pl]->addScore(2);
            }
        default:
            for (unsigned int pl : tab_max_scores[i].getFirsts()){
                m_players[pl]->addScore(1);
            }
        }
    }

    delete[] tab_max_scores;
}

void Game::notifyInterface(unsigned int code){
    if (!m_is_console){
        return readNotification(code);
    }
    m_target->notifyInterface(code);
}

void Game::endTurn(){
    m_token_to_add = nullptr;
    m_is_waiting_for_position = false;

    if (m_is_console){
        m_menu_validate = new CValidateMenu(this);
    }
    else {
        GraphXVue::instance()->show(current_player); // Update l'affichage
        GValidateMenu* gMenu = new GValidateMenu(this);
        m_menu_validate = gMenu;
        GraphXVue::instance()->addMenu(gMenu);
    }
    return m_menu_validate->show();
}


void Game::readNotification(unsigned int code){
    if (code == 1){
        Player *pl = nullptr;
        for (Menu<std::string>::Iterator it = m_player_menu->getIterator(); !it.isDone(); it++){
            std::cout << it.getValue() << std::endl;
            PlayerBoard* bd;
            if (m_is_console){
                bd = new CPlayerBoard(this);
            }
            else {
                bd = new GPlayerBoard(this);
            }
            pl = new Player(it.getValue(), bd);
            m_players.push_back(pl);
            //std::cout << m_players.back()->getName() << std::endl;
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
            if (key == "Use variant") {
                m_desc_cards = value;
                std::cout << "cartes des variantes configurees avec succes";
            }
            else if (key == "Use cards") {
                m_scorer.configureCards(value);
                m_desc_cards = value;
                std::cout << "cartes configurees avec succes";
            }
            if (key == "Test scroring") {
                readCards();
                scoreGame();
            }
            if (key == "Recover"){
                return resurrectGame();
                //return play();
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
        return m_player_menu->show();
        //return play();
    }

    if (code == 3){
        std::cout << "Received code 3" << std::endl;
        if (m_menu_token != nullptr){
            //throw CustomError("Menu token not initialized", 1);
            std::cout << "Game notified with code 3" << std::endl;
            std::vector<unsigned short int> params;
            for (Menu<unsigned short int>::Iterator it = m_menu_token->getIterator(); !it.isDone(); it++){
                params.push_back(it.getValue());
            }
            delete m_menu_token;
            m_menu_token = nullptr;
            if (params.size() == 2){
                getTileAndToken(params[0], params[1]);
            }
            else {
                getTileAndToken(params[0]);
            }
        }
        if (m_players[current_player]->getBoard() == nullptr){
            std::cout << "Cooked man" << std::endl;
            //throw CustomError();
        }
        m_players[current_player]->getBoard()->resetPointedCell();

        m_is_waiting_for_position = true;
        m_is_waiting_to_place_tile = true;
        return m_players[current_player]->getBoard()->show();
    }

    if (code == 4){
        std::cout << "Received code 4" << std::endl;
        if (m_is_waiting_for_position == false){
            return;
        }
        if (m_is_waiting_to_place_tile){ // Faut il traiter le clic
            HexCell target = HexCell(m_players[current_player]->getBoard()->getPointedCell());
            if (target != HexCell(MAX_SIZE, MAX_SIZE) && (m_players[current_player]->getBoard()->hasNeighbour(target)) && m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR()) == nullptr){
                m_is_waiting_to_place_tile = false;
                m_tile_to_add->setPos(target.getQ(), target.getR());

                /*unsigned short int rotation = 0;

                if (m_is_console){
                    std::cout << "Indiquez de combien de 1/6 de tour vous voulez tourner la tuile, dans le sens trigo : (0 à 5)";
                    std::string result;
                    std::cin >> result;
                    if (result.size() == 1){
                        if (result[0] < '6' && result[0] >= '0'){
                            rotation = result[0] - '0';
                        }
                    }
                }

                for (int i = 0; i < rotation; i++){
                    m_tile_to_add->Rotate(Trigonometric);
                }

                */
                std::cout << "Merci de choisir l'emplacement pour le pion faune : ";


                m_players[current_player]->getBoard()->addTile(*m_tile_to_add);
                m_tile_to_add = nullptr;

                //Checks if token can be placed
                bool has_place = false;
                std::cout << "Testing it : " << std::endl;
                const GameTile* ct = nullptr;
                for (PlayerBoard::Iterator it = m_players[current_player]->getBoard()->getIterator(); !it.isDone() && !has_place; it++){
                    ct = it.getValue();
                    for (unsigned short int i = 0; i < ct->getNbWildlife(); i++){
                        if (ct->getWildlife(i) == m_token_to_add->getWildlifeType() && ct->getToken() == nullptr){
                            has_place = true;
                        }
                    }
                }
                if (!has_place){
                    return endTurn();
                }

                m_players[current_player]->getBoard()->resetPointedCell();
                return m_players[current_player]->getBoard()->show();
            }
            else {
                m_players[current_player]->getBoard()->resetPointedCell();
                return m_players[current_player]->getBoard()->show();
            }
        }
        else {
            HexCell target = HexCell(m_players[current_player]->getBoard()->getPointedCell());
            if (target != HexCell(MAX_SIZE, MAX_SIZE) && (m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR()) != nullptr) && (m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR())->getToken() == nullptr)){
                const GameTile* tile = m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR());
                for (int i = 0; i < tile->getNbWildlife(); i++){
                    if (m_token_to_add->getWildlifeType() == tile->getWildlife(i)){
                        if (tile->isKeystone()){
                            m_players[current_player]->addNatureToken();
                        }
                        //m_players[current_player]->getBoard()->getTile(target.getQ(), target.getR())->setWildLifeToken(m_token_to_add);
                        m_players[current_player]->getBoard()->addToken(m_token_to_add, target);
                        if (m_is_console){
                            std::cout << "Le token a bien été placé." << std::endl;
                        }
                        return endTurn();
                    }
                }

                std::cout << "Token not good" << std::endl;
                m_players[current_player]->getBoard()->resetPointedCell();
                return m_players[current_player]->getBoard()->show();
            }
            else {
                std::cout << "Pos not good" << std::endl;
                m_players[current_player]->getBoard()->resetPointedCell();
                return m_players[current_player]->getBoard()->show();
            }
        }
    }

    else if (code == 5){
        if (m_menu_validate == nullptr){
            std::cout << "Validate menu not good" << std::endl;
            return;
        }
        unsigned short int control = 0;
        for (Menu<bool>::Iterator it = m_menu_validate->getIterator(); !it.isDone(); it++){
            if (control >= 1){
                return;
            }
            control++;
            if (it.getValue()){
                m_decktile->validateChanges();
                current_player++;
                if (current_player == m_nb_players){
                    current_player = 0;

                    current_tour++;
                    GraphXVue::instance()->nextTurn();
                    m_message_box->addMessage("Tour numéro " + std::to_string(current_tour + 1), 0, 0);
                    saveGame();
                    if (current_tour == MAX_TURN){
                        delete m_menu_validate;
                        m_menu_validate = nullptr;
                        return scoreGame();
                    }
                }
            }
            else {
                if (m_players[current_player]->getBoard()->getLast()->isKeystone()){
                    m_players[current_player]->removeNatureToken();
                }
                m_players[current_player]->getBoard()->removeLast();
            }
        }
        delete m_menu_validate;
        m_menu_validate = nullptr;
        return makePlayerTurn();
    }
}

void Game::readCards(std::string path){
    m_starter_cards[0][0] = new GameTile("2223333245");
    m_starter_cards[0][1] = new GameTile("55555515");
    m_starter_cards[0][2] = new GameTile("444111213");

    m_starter_cards[1][0] = new GameTile("3331113423");
    m_starter_cards[1][1] = new GameTile("22222214");
    m_starter_cards[1][2] = new GameTile("444555215");

    m_starter_cards[2][0] = new GameTile("1112223354");
    m_starter_cards[2][1] = new GameTile("44444411");
    m_starter_cards[2][2] = new GameTile("333555212");

    m_starter_cards[3][0] = new GameTile("5551113123");
    m_starter_cards[3][1] = new GameTile("33333312");
    m_starter_cards[3][2] = new GameTile("444222245");

    m_starter_cards[4][0] = new GameTile("4443333134");
    m_starter_cards[4][1] = new GameTile("11111113");
    m_starter_cards[4][2] = new GameTile("555222252");

    for (int i = 0; i < 5; i ++){
        m_starter_cards[i][0]->Rotate(Trigonometric);
        m_starter_cards[i][0]->setPos(-1, 1);
        m_starter_cards[i][1]->setPos(0, 0);
        m_starter_cards[i][2]->setPos(0, 1);

    }

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
        m_cards[0] = new GameTile("11111111");
        m_cards[1] = new GameTile("222222212");
        m_cards[2] = new GameTile("33333313");
        m_cards[3] = new GameTile("44444414");
        m_cards[4] = new GameTile("55555515");
        m_cards[5] = new GameTile("111222234");
        m_cards[6] = new GameTile("3332223213");
        m_cards[7] = new GameTile("444222215");
        m_cards[8] = new GameTile("5552223214");

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
        m_cards[i - 1] = new GameTile(parts[i].toStdString());
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

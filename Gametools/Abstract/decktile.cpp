#include "decktile.hpp"
#include <algorithm>
#include <random>

DeckTile &DeckTile::getInstance(){
    throw CustomError("Virtual class got called", 301);
}


DeckTile::DeckTile() : Printable(), SalvableThing() {
    m_deck_tiles.reserve(120);
    m_deck_token.reserve(120);

    for (int i = 0; i < 4; i++){
        m_tiles[i] = nullptr;
    }
}

DeckTile::~DeckTile(){

}

void DeckTile::reinterpetString(const std::string& def){
    //Permet de récupérer la pioche à partir de son élément de sauvegarde
    std::vector<std::string> params = SalvableThing::separateParams(def);
    if (params.size() != 4){
        throw 99;
    }
    for (unsigned short i = 0; i < 4; i++){
        std::vector<std::string> param_sep = separateParams(params[i], ',');
        //std::cout << "Separated : " << param_sep[0] << ", " << param_sep[1] << std::endl;
        m_expected_token.push_back(stringToInt(param_sep[0]));
        m_expected_card.push_back(stringToInt(param_sep[1]));
    }
}



std::string DeckTile::getSaveString() const {
    //Permet de générer l'élément de sauvegarde d'une pioche
    std::string rt = "{";
    for (unsigned char i = 0; i < 4; i++){
        rt += std::to_string(m_displayed_tokens[i]->getWildlifeType()) + ",";
        rt += std::to_string(m_tiles[i]->getId()) + ";";
    }
    rt += "}";
    return rt;
}

GameTile* DeckTile::getTile(unsigned short int i){
    if (i < 4){
        return m_tiles[i];
    }
    throw CustomError("Tile not in range", 202);
}

void DeckTile::validateChanges(){
    if (m_id_card_to_rm < 4 && m_id_card_to_rm < 4){
        m_displayed_tokens[m_id_token_to_rm] = nullptr;
        m_tiles[m_id_card_to_rm] = nullptr;
        fillPlate();
    }
    m_id_token_to_rm = 5;
    m_id_card_to_rm = 5;
}


void DeckTile::addTile(GameTile* tile){
    //Ajoute une tuile (cf google trad). On l'ajoute dans le "sac de tuiles" dans lequel on prend pour générer la pioche face visible.
    m_deck_tiles.push_back(tile);
    shuffle();
}

void DeckTile::addToken(const WildlifeToken* token){
    m_deck_token.push_back(token);
    shuffle();
}

void DeckTile::shuffle(){
    //Mélange les tuiles faces cachée. C'est l'équivalent de secouer le sac avant de piocher
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(std::begin(m_deck_tiles), std::end(m_deck_tiles), rng);
    std::shuffle(std::begin(m_deck_token), std::end(m_deck_token), rng);
}

void DeckTile::clearTokens(){
    //Permet de changer les pions faune dans le cas où ils sont trop nombreux.
    for (int i = 0; i < 4; i++){
        m_deck_token.push_back(m_displayed_tokens[i]);
        m_displayed_tokens[i] = nullptr;
        shuffle();
        fillPlate();
    }
}


int DeckTile::fillPlate(){
    /*Permet de remplir la liste des tuiles et tokens*/
    m_can_flush = false;
    for (int i = 0; i < 4; i++){
        if (m_tiles[i] == nullptr){
            //std::cout << "Adding " << m_deck_tiles[m_deck_tiles.size()-1] << std::endl;
            if (m_deck_tiles.empty() == false){
                m_tiles[i] = m_deck_tiles[m_deck_tiles.size()-1];
                m_deck_tiles.pop_back();
            }
            else {
                return 1;
            }
        }
        if (m_displayed_tokens[i] == nullptr){
            if (m_deck_token.empty() == false){
                m_displayed_tokens[i] = m_deck_token.back();
                m_deck_token.pop_back();
            }
            else {
                return 2;
            }
        }
    }
    unsigned short int nb_same_token = 1;
    for (int i = 1; i < 4; i++){
        if (m_displayed_tokens[0]->getWildlifeType() == m_displayed_tokens[i]->getWildlifeType() || (m_displayed_tokens[1]->getWildlifeType() == m_displayed_tokens[i]->getWildlifeType()) && i != 1){
            nb_same_token++;
        }
    }
    if (nb_same_token == 4){
        clearTokens();
    }
    else if (nb_same_token == 3){
        m_can_flush = true;
    }
    return 0;
}

std::tuple<GameTile*, const WildlifeToken*> DeckTile::getCouple(int id_card, int id_token){
    /*Permet de récupérer les tokens et tuiles séléctionnés par l'utilisateur pour les afficher*/
    if (id_token == 65535){
        id_token = id_card;
    }
    if (id_card > 4 || id_card < 0 || id_token > 4 || id_token < 0 ){
        return std::tuple<GameTile*, const WildlifeToken*>(nullptr, nullptr);
    }
    const WildlifeToken* token_rt = m_displayed_tokens[id_token];
    GameTile* tiles_rt = m_tiles[id_card];

    m_id_card_to_rm = id_card;
    m_id_token_to_rm = id_token;

    return std::tuple<GameTile*, const WildlifeToken*>(tiles_rt, token_rt);
}

#include "decktile.hpp"
#include <algorithm>
#include <random>
#include <iostream>

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

GameTile* DeckTile::getTile(unsigned short int i){
    if (i < 4){
        return m_tiles[i];
    }
}


void DeckTile::addTile(GameTile* tile){
    //std::cout << "Added tile : " << tile << std::endl;
    m_deck_tiles.push_back(tile);
    //shuffle();
}

void DeckTile::addToken(const WildlifeToken* token){
    m_deck_token.push_back(token);
    //shuffle();
}

void DeckTile::shuffle(){
    std::cout << "Shuffling" << std::endl;
    std::default_random_engine rng = std::default_random_engine {};
    std::shuffle(std::begin(m_deck_tiles), std::end(m_deck_tiles), rng);
    std::shuffle(std::begin(m_deck_token), std::end(m_deck_token), rng);
}

void DeckTile::clearTokens(){
    for (int i = 0; i < 4; i++){
        m_deck_token.push_back(m_displayed_tokens[i]);
        m_displayed_tokens[i] = nullptr;
        shuffle();
        fillPlate();
    }
}


int DeckTile::fillPlate(){
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
    return 0;
}

std::tuple<GameTile*, const WildlifeToken*> DeckTile::getCouple(int id_card, int id_token){
    if (id_token == 65535){
        id_token = id_card;
    }
    if (id_card > 4 || id_card < 0 || id_token > 4 || id_token < 0 ){
        return std::tuple<GameTile*, const WildlifeToken*>(nullptr, nullptr);
    }
    const WildlifeToken* token_rt = m_displayed_tokens[id_token];
    GameTile* tiles_rt = m_tiles[id_card];

    m_displayed_tokens[id_token] = nullptr;
    m_tiles[id_card] = nullptr;
    fillPlate();

    return std::tuple<GameTile*, const WildlifeToken*>(tiles_rt, token_rt);
}

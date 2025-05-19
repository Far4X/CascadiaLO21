#include "decktile.hpp"
#include <algorithm>
#include <random>

DeckTile &DeckTile::getInstance(){
    throw CustomError("Virtual class got called", 301);
}


DeckTile::DeckTile() : TileHolder(4, 1) {

}

void DeckTile::addTile(GameTile* tile){
    m_deck_tiles.push_back(tile);
}

void DeckTile::addToken(const WildlifeToken* token){
    m_deck_token.push_back(token);
}

void DeckTile::shuffle(){
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
        if (getTile(i, 0) == nullptr){
            if (m_deck_tiles.empty() == false){
                m_tiles[i][0] = m_deck_tiles.back();
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
    if (id_token == -1){
        id_token = id_card;
    }
    if (id_card > 4 || id_card < 0 || id_token > 4 || id_token < 0 ){
        return std::tuple<GameTile*, const WildlifeToken*>(nullptr, nullptr);
    }
    const WildlifeToken* token_rt = m_displayed_tokens[id_token];
    GameTile* tiles_rt = m_tiles[id_card][0];

    m_displayed_tokens[id_token] = nullptr;
    m_tiles[id_card][0] = nullptr;
    fillPlate();

    return std::tuple<GameTile*, const WildlifeToken*>(tiles_rt, token_rt);

}

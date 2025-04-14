#include "Gametools/gametile.hpp"

GameTile::GameTile(Biome biomes[6], Wildlife *type = nullptr, int num_types = 0, int posx = 0, int posy = 0, int rotation = 0){
    for (int i = 0; i < 6; i++){
        m_biome =
    }
    m_top_biome = top;
    m_btm_biome = btm;
    m_possible_wltoken = new Wildlife[num_types];
    for (int i = 0; i < num_types; i++){
        m_possible_wltoken[i] = type[i];
    }
    m_position = HexTile(posx, posy);
}

GameTile::~GameTile(){
    delete[] m_possible_wltoken;
}

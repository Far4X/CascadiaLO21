#include "gametile.hpp"

GameTile::GameTile(Biome top, Biome btm, Wildlife *type, int num_types, int posx, int posy, int rotation){
    m_top_biome = top;
    m_btm_biome = btm;
    m_possible_wltoken = new Wildlife[num_types];
    for (int i = 0; i < num_types; i++){
        m_possible_wltoken[i] = type[i];
    }
    m_posx = posx;
}

GameTile::~GameTile(){
    delete[] m_possible_wltoken;
}

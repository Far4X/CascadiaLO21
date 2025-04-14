#include "gametile.hpp"

GameTile::GameTile(unsigned int id, Biome biomes[6], Wildlife *type, int num_types, int posx, int posy) : HexCell(posx, posy), m_id(id){
    for (int i = 0; i < 6; i++){
        m_biomes[i] = biomes[i];
    }
    m_possible_wltoken = new Wildlife[num_types];
    for (int i = 0; i < num_types; i++){
        m_possible_wltoken[i] = type[i];
    }
}

GameTile::~GameTile(){
    delete[] m_possible_wltoken;
}

void GameTile::Rotate(Rotation rota){
    if (rota == Anti_Trigonometric){
        Biome tmp = m_biomes[5];
        for (int i = 6; i > 0; i--){
            m_biomes[i] = m_biomes[i-1];
        }
        m_biomes[0] = tmp;
        m_rotation++;
        m_rotation%=6;
        return;
    }
    Biome tmp = m_biomes[0];
    for (int i = 0; i < 5; i++){
        m_biomes[i] = m_biomes[i+1];
    }
    m_rotation = (m_rotation-1)%6;
    m_biomes[5] = tmp;
    return;
}

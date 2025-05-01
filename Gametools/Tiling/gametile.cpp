#include "gametile.hpp"

GameTile::GameTile(unsigned int id, Biome biomes[6], Wildlife *type, int num_types, int posx, int posy) : HexCell(posx, posy), m_id(id){
    for (int i = 0; i < 6; i++){
        m_biomes[i] = biomes[i];
    }
    m_numtypes = num_types;
    m_possible_wltoken = new Wildlife[num_types];
    for (int i = 0; i < num_types; i++){
        m_possible_wltoken[i] = type[i];
    }

}

GameTile::GameTile(int id, std::string description) : HexCell(), m_id(id){
    for (int i = 0; i < 6; i++){
        switch (description[i]) {
        case '1' :
            m_biomes[i] = Forest;
            break;
        case '2' :
            m_biomes[i] = Wetland;
            break;
        case '3' :
            m_biomes[i] = River;
            break;
        case '4':
            m_biomes[i] = Mountain;
            break;
        case '5':
            m_biomes[i] = Prairie;
            break;
        default:
            break;
        }
    }
    m_numtypes = description[6] - '0';

    m_possible_wltoken = new Wildlife[m_numtypes];
    for (int i = 7; i < m_numtypes + 7; i++){
        switch (description[i]) {
        case '1' :
            m_possible_wltoken[i] = Bear;
            break;
        case '2' :
            m_possible_wltoken[i] = Salmon;
            break;
        case '3' :
            m_possible_wltoken[i] = Elk;
            break;
        case '4':
            m_possible_wltoken[i] = Hawk;
            break;
        case '5':
            m_possible_wltoken[i] = Fox;
            break;
        default:
            break;
        }
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

std::string GameTile::getSaveString() const{
    return "";
}

char** getRepresentation(const GameTile& tile, unsigned short int size){
    unsigned short int height = 2*size+1;
    unsigned short int width = 4*size;
    char **rt = new char*[height];
    for (unsigned short int i = 0; i < height; i++){
        rt[i] = new char[width];
        for (int j = 0; j < width; j++){
            rt[i][j] = ' ';
        }
    }

    //Draw hex
    for (int i = 0; i < size; i++){
        rt[size + 1 + i][i] = '\\';
        rt[size - i][i] = '/';
        rt[0][i+size] = '_';
        rt[height-1][i+size] = '_';
        rt[0][3*size -i -1] = '_';
        rt[height-1][3*size -i -1] = '_';

    }
    tile.getID();
    return rt;
}


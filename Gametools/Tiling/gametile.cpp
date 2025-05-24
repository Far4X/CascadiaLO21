#include "gametile.hpp"
#include <iostream>

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
            m_possible_wltoken[i-7] = Bear;
            break;
        case '2' :
            m_possible_wltoken[i-7] = Salmon;
            break;
        case '3' :
            m_possible_wltoken[i-7] = Elk;
            break;
        case '4':
            m_possible_wltoken[i-7] = Hawk;
            break;
        case '5':
            m_possible_wltoken[i-7] = Fox;
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

char** getRepresentation(const GameTile* tile, unsigned short int size, unsigned int max_size, bool add_pos){ //Merge with hexcell function
    unsigned short int height = 2*size+1;
    unsigned short int width = 4*size;
    char **rt = new char*[height];
    for (unsigned short int i = 0; i < height; i++){
        rt[i] = new char[width];
        for (int j = 0; j < width; j++){
            rt[i][j] = ' ';
        }
    }

    if (tile == nullptr){
        return rt;
    }

    //Draw hex
    for (int i = 0; i < size; i++){
        rt[0][i+size] = '_';
        rt[height-1][i+size] = '_';
        rt[0][3*size -i -1] = '_';
        rt[height-1][3*size -i -1] = '_';

        rt[size][i] = '_';
        rt[size][2*size-i-1] = '_';
        rt[size][i+2*size] = '_';
        rt[size][4*size - i - 1] = '_';


        rt[size + 1 + i][2*size - i - 1] = '/';
        rt[size + 1 + i][i] = '\\';
        rt[size + 1 + i][4*size - i - 1] = '/';
        rt[height - i - 1][3*size - 1 - i] = '\\';


        rt[i+1][size + i] = '\\';
        rt[i+1][3*size+ i] = '\\';
        rt[size - i][i+2*size] = '/';
        rt[size - i][i] = '/';

    }

    //Fill hex
    std::cout << tile << std::endl;
    for (int i = 0; i < 6; i++){
        char filling;
        switch (tile->getBiome(i)) {
        case Forest:
            filling = '@';
            break;
        case Wetland:
            filling = ':';
            break;
        case Mountain:
            filling = '^';
            break;
        case River:
            filling = '~';
            break;
        case Prairie:
            filling = '|';
            break;
        default:
            break;
        }
        unsigned short int padding_x;
        unsigned short int padding_y;
        if (i % 2 == 0){
            //Down triangle
            if (i == 0){
                padding_y = size + 1;
                padding_x = 1;
            }
            else if (i == 2){
                padding_y = 2*size + 1;
                padding_x = size + 1;
            }
            else if (i == 4){
                padding_y = 1;
                padding_x = size + 1;
            }
            for (int j = 0; j < size - 1; j++){
                for (int k = size - j - 1; k>0; k--){
                    rt[padding_x + j][padding_y + j + k -1] = filling;
                    rt[padding_x + j][padding_y - j - k + 2*size - 2] = filling;
                }
            }
        }
        else {
            //Up triangle
            if (i == 1){
                padding_x = 1;
                padding_y = 2*size + 1;
            }
            else if (i == 3){
                padding_x = size + 1;
                padding_y = size + 1;
            }
            else if (i == 5){
                padding_x = 1;
                padding_y = 1;
            }
            for (int j = 0; j < size - 1; j++){
                for (int k = 1; k <= j; k++){
                    rt[padding_x + j][padding_y - k + size - 1] = filling;
                    rt[padding_x + j][padding_y + k + size - 2] = filling;
                }
            }
        }
    }

    // Adding informations

    if (add_pos){
        HexCell::Offset pos = HexCell::axialToOffset(*tile, max_size);
        rt[size][1] = char(pos.getCol() / 10) + '0';
        rt[size][2] = char(pos.getCol() % 10) + '0';
        rt[size][3] = ',';
        rt[size][4] = char(pos.getRow() / 10) + '0';
        rt[size][5] = char(pos.getRow() % 10) + '0';
    }
    if (tile->getToken() == nullptr){
        std::cout << "Has " << tile->getNbWildlife() << " wildlife" << std::endl;
        for (int i = 0; i < tile->getNbWildlife(); i++){
            char out = ' ';
            switch (tile->getWildlife(i)){
            case Bear :
                out = 'b';
                break;
            case Salmon :
                out = 's';
                break;
            case Hawk :
                out = 'h';
                break;
            case Elk :
                out = 'e';
                break;
            case Fox :
                out = 'f';
                break;
            default :
                std::cout << "Not here" << std::endl;
                break;
            }
            rt[size][2*size + i+1] = out;
        }
    }    
    else {
        char out = ' ';
        switch(tile->getToken()->getWildlifeType()){
        case Bear :
            out = 'B';
            break;
        case Salmon :
            out = 'S';
            break;
        case Hawk :
            out = 'H';
            break;
        case Elk :
            out = 'E';
            break;
        case Fox :
            out = 'F';
            break;
        }
        rt[size][2*size + 1] = out;
    }

    if (tile->isKeystone()){
        rt[size-1][3] = '#';
    }

    return rt;
}

void GameTile::setPos(int const &q, int const &r){
    this->setQ(q);
    this->setR(r);
}

bool GameTile::isKeystone(const std::string& description)const {
    if (description.size() < 6) {
        for (int i = 1; i < 6; i++){
            if (m_biomes[i] != m_biomes[0]){
                return false;
            }
        }
        return true;
    }


    char first = description[0];
    for (int i = 1; i < 6; ++i) {
        if (description[i] != first) {
            return false;
        }
    }
    return true;
}

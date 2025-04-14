#ifndef GAMETILE_HPP
#define GAMETILE_HPP
#include "wildlifetoken.hpp"
#include "hexcell.hpp"

enum Biome {Forest, Wetland, River, Mountain, Prairie};
enum Rotation {Trigonometric, Anti_Trigonometric};

class GameTile : public HexCell { //Or inherits public hextile; if not rename HexTile HexTileCoord
    //Hexcell m_position;
    Biome m_biomes[6];
    unsigned char m_rotation;
    WildlifeToken *m_wltoken = nullptr;
    Wildlife *m_possible_wltoken = nullptr;
    int m_numtypes;

public:
    GameTile(Biome biomes[6], Wildlife *type = nullptr, int num_types = 0, int posx = 0, int posy = 0, int rotation = 0);
    ~GameTile();
    void Rotate(Rotation dir = Anti_Trigonometric);
    int draw();
};

#endif // GAMETILE_HPP

#ifndef GAMETILE_HPP
#define GAMETILE_HPP
#include "wildlifetoken.hpp"
#include "hextile.hpp"

enum Biome {Forest, Wetland, River, Mountain, Prairie};
enum Rotation {Trigonometric, Anti_Trigonometric};

class GameTile { //Or inherits public hextile; if not rename HexTile HexTileCoord
    HexTile m_position;
    Biome m_top_biome;
    Biome m_btm_biome;
    unsigned char m_rotation;
    WildlifeToken *m_wltoken = nullptr;
    Wildlife *m_possible_wltoken = nullptr;
    int m_numtypes;

public:
    GameTile(Biome top = Mountain, Biome south = Mountain, Wildlife *type = nullptr, int num_types = 0, int posx = 0, int posy = 0, int rotation = 0);
    ~GameTile();
    void Rotate(Rotation dir = Anti_Trigonometric);
    int draw();
};

#endif // GAMETILE_HPP

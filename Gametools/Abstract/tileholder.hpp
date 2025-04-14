#ifndef TILEHOLDER_HPP
#define TILEHOLDER_HPP

#include "../Tiling/gametile.hpp"
#include "salvablething.hpp"
#include "printable.hpp"

//Q analog x
//R analog y

class TileHolder : public Printable, SalvableThing{
    GameTile ***m_tiles;
    int m_size_x;
    int m_size_y;

public:
    TileHolder(int size_x, int size_y);
    ~TileHolder();
    GameTile* getTile(int posx, int posy) const;
    void addTile(GameTile& tile, unsigned int* q = nullptr, unsigned int* r = nullptr, bool overwrite = false);
    virtual void print() = 0;
};

#endif // TILEHOLDER_HPP

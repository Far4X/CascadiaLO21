#ifndef TILEHOLDER_HPP
#define TILEHOLDER_HPP

#include "../Tiling/gametile.hpp"
#include "salvablething.hpp"
#include "printable.hpp"
#include <vector>
#include <utility>


//Q analog x
//R analog y

class TileHolder : public Printable, SalvableThing{
protected:
    GameTile ***m_tiles;
    int m_size_x;
    int m_size_y;

public:
    TileHolder(int size_x, int size_y);
    virtual ~TileHolder();
    GameTile* getTile(int posx, int posy) const;
    void addTile(GameTile& tile, int x, int y, bool overwrite = false);
    virtual void show() = 0;
    std::vector<std::pair<int, int>> getFilledTilePositions() const;
    std::vector<HexCell> getFreeAdjacentCells(int max_size) const;


};

#endif // TILEHOLDER_HPP

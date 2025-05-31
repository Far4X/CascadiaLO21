#ifndef TILEHOLDER_HPP
#define TILEHOLDER_HPP

#include "../Tiling/gametile.hpp"
#include "salvablething.hpp"
#include "printable.hpp"
#include <vector>
#include <utility>


class TileHolder : public Printable, SalvableThing{
    /*Classe qui permet de stocker des tuiles dans un tableau 2D*/
protected:
    GameTile ***m_tiles;
    int m_size_x;
    int m_size_y;

public:
    class Iterator {
        friend class TileHolder;
        const TileHolder* const m_holder = nullptr;
        unsigned short int m_x = 0;
        unsigned short int m_y = 0;
        inline Iterator(const TileHolder* tar) : m_holder(tar){if(!isDone())(*this)++;};
        Iterator(const Iterator& tar) = delete;
        Iterator& operator=(const Iterator& tar)const = delete;

    public :
        Iterator& operator++(int);
        inline const GameTile* getValue() const {return m_holder->getTile(m_x, m_y);};
        bool isDone() const;
    };
    Iterator getIterator() const {return Iterator(this);}
    TileHolder(int size_x, int size_y);
    virtual ~TileHolder();
    GameTile* getTile(int posx, int posy) const;
    void addTile(GameTile& tile, int x, int y, bool overwrite = false);
    void removeTile(int x, int y);
    virtual void show() = 0;
    std::vector<std::pair<int, int>> getFilledTilePositions() const;
    std::vector<HexCell> getFreeAdjacentCells(int max_size) const;


};

#endif // TILEHOLDER_HPP

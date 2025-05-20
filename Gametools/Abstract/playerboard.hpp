#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "../Tiling/gametile.hpp"
#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
    //unsigned short int m_q_center;
    //unsigned short int m_r_center;
    HexCell pointed_cell;
    bool m_want_use_naturetoken = false;

public:
    static inline HexCell::Offset axialToOffset(const HexCell& hex){return HexCell::axialToOffset(hex, MAX_SIZE);};
    static inline HexCell offsetToAxial(const HexCell::Offset& off){return HexCell::offsetToAxial(off, MAX_SIZE);};
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    //void moveHz(short int step = 1);
    //void moveVt(short int step = 1);
    inline bool getIntentionToken() const {return m_want_use_naturetoken;};
    inline void setIntentionToken(bool val) {m_want_use_naturetoken = val;};
    void addTile(GameTile& tile);
    bool hasNeighbour(unsigned short int x, unsigned short int y);
    inline HexCell getPointedCell() const {return pointed_cell;};
};

#endif // PLAYERBOARD_HPP

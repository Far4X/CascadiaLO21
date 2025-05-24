#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "tileholder.hpp"
#include "notifiableinterface.hpp"

class PlayerBoard : public TileHolder {
    //unsigned short int m_q_center;
    //unsigned short int m_r_center;
protected :
    HexCell m_pointed_cell = HexCell(0, 0);
    bool m_want_use_naturetoken = false;
    NotifiableInterface* m_target = nullptr;

public:
    virtual ~PlayerBoard() = default;
    static inline HexCell::Offset axialToOffset(const HexCell& hex){return HexCell::axialToOffset(hex, MAX_SIZE);};
    static inline HexCell offsetToAxial(const HexCell::Offset& off){return HexCell::offsetToAxial(off, MAX_SIZE);};
    PlayerBoard(NotifiableInterface* tar = nullptr);
    GameTile* getNeighborTile(const GameTile& tile, Direction d) const;
    std::vector<GameTile*> getNeighborTiles(const GameTile& tile) const;
    void show() override;
    std::string getSaveString() const override;
    //void moveHz(short int step = 1);
    //void moveVt(short int step = 1);
    inline bool getIntentionToken() const {return m_want_use_naturetoken;};
    inline void setIntentionToken(bool val) {m_want_use_naturetoken = val;};
    void addTile(GameTile& tile);
    bool hasNeighbour(const HexCell& pos);
    inline HexCell getPointedCell() const {return m_pointed_cell;};
    inline void resetPointedCell() {m_pointed_cell = HexCell(0,0);};
    GameTile* getTile(int const &q, int const &r) const;
};

#endif // PLAYERBOARD_HPP

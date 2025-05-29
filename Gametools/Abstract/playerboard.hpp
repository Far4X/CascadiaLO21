#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "tileholder.hpp"
#include "notifiableinterface.hpp"

class PlayerBoard : public TileHolder {
    //unsigned short int m_q_center;
    //unsigned short int m_r_center;
    HexCell m_pos_last_token = HexCell(MAX_SIZE + 1, MAX_SIZE+1);
    HexCell m_pos_last_tile = HexCell(MAX_SIZE + 1, MAX_SIZE+1);

protected :
    HexCell m_pointed_cell = HexCell(MAX_SIZE, MAX_SIZE);
    //bool m_want_use_naturetoken = false;
    NotifiableInterface* m_target = nullptr;

public:
    virtual ~PlayerBoard() = default;
    static inline HexCell::Offset axialToOffset(const HexCell& hex){return HexCell::axialToOffset(hex, MAX_SIZE);};
    static inline HexCell offsetToAxial(const HexCell::Offset& off){return HexCell::offsetToAxial(off, MAX_SIZE);};
    PlayerBoard(NotifiableInterface* tar = nullptr);
    GameTile* getNeighborTile(const GameTile& tile, Direction d) const;
    std::vector<GameTile*> getNeighborTiles(const GameTile& tile) const;
    //virtual void show() = 0;
    std::string getSaveString() const override;
    //inline bool getIntentionToken() const {return m_want_use_naturetoken;};
    //inline void setIntentionToken(bool val) {m_want_use_naturetoken = val;};
    void addTile(GameTile& tile);
    void addToken(const WildlifeToken* token, HexCell& pos_target);
    void removeLast();
    bool hasNeighbour(const HexCell& pos);
    inline HexCell getPointedCell() const {return m_pointed_cell;};
    inline void resetPointedCell() {m_pointed_cell = HexCell(MAX_SIZE,MAX_SIZE);};
    inline void setPointedCell(HexCell cell){m_pointed_cell = cell;};
    inline NotifiableInterface* getTarget()const{return m_target;};
    GameTile* getTile(int const &q, int const &r) const;
    void pointCell(int q, int r) ;

};

#endif // PLAYERBOARD_HPP

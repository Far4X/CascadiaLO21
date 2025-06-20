#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "tileholder.hpp"
#include "notifiableinterface.hpp"

class PlayerBoard : public TileHolder {
    //Classe qui permet de représenter l'ensemble des tuiles d'un joueur au bon endroit
    HexCell m_pos_last_token = HexCell(MAX_SIZE + 1, MAX_SIZE+1);
    HexCell m_pos_last_tile = HexCell(MAX_SIZE + 1, MAX_SIZE+1);
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int>> m_required_cards;// Used when ressucite. Store cards with id, posx, posy, rotation, token

protected :
    HexCell m_pointed_cell = HexCell(MAX_SIZE, MAX_SIZE);
    NotifiableInterface* m_target = nullptr;

public:
    virtual ~PlayerBoard();
    static inline HexCell::Offset axialToOffset(const HexCell& hex){return HexCell::axialToOffset(hex, MAX_SIZE);};
    static inline HexCell offsetToAxial(const HexCell::Offset& off){return HexCell::offsetToAxial(off, MAX_SIZE);};
    PlayerBoard(NotifiableInterface* tar = nullptr);
    GameTile* getNeighborTile(const GameTile& tile, Direction d) const;
    std::vector<GameTile*> getNeighborTiles(const GameTile& tile) const;
    int getNbNeighbors(const GameTile& tile) const;
    int getNbSameNeighbors(const GameTile& tile, Wildlife animal) const;
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    void addTile(GameTile& tile);
    void addToken(const WildlifeToken* token, HexCell& pos_target);
    void removeLast();
    const GameTile* getLast();
    bool hasNeighbour(const HexCell& pos);
    inline HexCell getPointedCell() const {return m_pointed_cell;};
    inline void resetPointedCell() {m_pointed_cell = HexCell(MAX_SIZE,MAX_SIZE);};
    inline void setPointedCell(HexCell cell){m_pointed_cell = cell;};
    inline NotifiableInterface* getTarget()const{return m_target;};
    GameTile* getTile(int const &q, int const &r) const;
    GameTile* getOffsetTile(int const &x, int const &y) const;
    void pointCell(int q, int r);
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int> getNextNeededCard();
    bool hasAllCards() const {return m_required_cards.size() == 0;}
    void reinterpretString(const std::string &desc);
};

#endif // PLAYERBOARD_HPP

#ifndef DECKCARD_HPP
#define DECKCARD_HPP

#include "tileholder.hpp"
#include <vector>

class DeckTile : public Printable, public SalvableThing {
protected :
    std::vector<GameTile*> m_deck_tiles;
    std::vector<const WildlifeToken*> m_deck_token;
    /*GameTile** m_deck_tiles;
    const WildlifeToken** m_deck_token;
    unsigned short int m_num_tiles = 0;
    unsigned short int m_num_token = 0;*/

    GameTile* m_tiles[4];

    const WildlifeToken* m_displayed_tokens[4];
    static DeckTile& getInstance();
    DeckTile(const DeckTile &tar) = delete;
    DeckTile &operator=(const DeckTile &tar) = delete;
    DeckTile();
    virtual ~DeckTile();
public:
    GameTile *getTile(unsigned short int i);
    int fillPlate();
    void addTile(GameTile* tile);
    void addToken(const WildlifeToken* token);
    void shuffle();
    void clearTokens();
    std::tuple<GameTile*, const WildlifeToken*> getCouple(int id_card, int id_token = -1);
};

#endif // DECKCARD_HPP

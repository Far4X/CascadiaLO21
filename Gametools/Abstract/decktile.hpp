#ifndef DECKCARD_HPP
#define DECKCARD_HPP

#include "tileholder.hpp"
#include <vector>

class DeckTile : public TileHolder {
    std::vector<const GameTile*> m_deck_tiles;
    std::vector<const WildlifeToken*> m_deck_token;

    const WildlifeToken* m_displayed_tokens[4];
public:
    DeckTile();
    int fillPlate();
};

#endif // DECKCARD_HPP

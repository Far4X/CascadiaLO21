#ifndef DECKCARD_HPP
#define DECKCARD_HPP

#include "tileholder.hpp"
#include <vector>

class DeckTile : public TileHolder {
protected :
    std::vector<GameTile*> m_deck_tiles;
    std::vector<const WildlifeToken*> m_deck_token;

    const WildlifeToken* m_displayed_tokens[4];
    static DeckTile& getInstance();
    DeckTile(const DeckTile &tar) = delete;
    DeckTile &operator=(const DeckTile &tar) = delete;
    DeckTile();
    ~DeckTile() = default;
public:
    int fillPlate();
    void addTile(GameTile* tile);
    void addToken(const WildlifeToken* token);
    void shuffle();
    void clearTokens();
    std::tuple<GameTile*, const WildlifeToken*> getCouple(int id_card, int id_token = -1);
};

#endif // DECKCARD_HPP

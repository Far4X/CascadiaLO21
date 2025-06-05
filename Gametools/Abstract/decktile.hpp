#ifndef DECKCARD_HPP
#define DECKCARD_HPP

#include "tileholder.hpp"
#include <vector>

class DeckTile : public Printable, public SalvableThing {
    /*Classe qui permet de représenter la pioche et les tuiles et tokens visibles sur la table*/
protected :
    std::vector<GameTile*> m_deck_tiles;
    std::vector<const WildlifeToken*> m_deck_token;
    GameTile* m_tiles[4];
    const WildlifeToken* m_displayed_tokens[4];

    void reinterpetString(const std::string& def);
    std::string getSaveString() const override;
    static DeckTile& getInstance();
    DeckTile(const DeckTile &tar) = delete;
    DeckTile &operator=(const DeckTile &tar) = delete;
    DeckTile();
    virtual ~DeckTile();
    bool m_can_flush = false;
    unsigned short int m_id_card_to_rm = 5;
    unsigned short int m_id_token_to_rm = 5;

public:
    GameTile *getTile(unsigned short int i);
    int fillPlate();
    inline bool canFlushWithoutNaturetoken() const {return m_can_flush;};
    void addTile(GameTile* tile);
    void addToken(const WildlifeToken* token);
    void shuffle();
    void clearTokens();
    void validateChanges();
    std::tuple<GameTile*, const WildlifeToken*> getCouple(int id_card, int id_token = -1);
};

#endif // DECKCARD_HPP

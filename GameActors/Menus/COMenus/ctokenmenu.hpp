#ifndef CTOKENMENU_HPP
#define CTOKENMENU_HPP

#include "cmenu.hpp"
#include "../../../Gametools/Abstract/decktile.hpp"

class CTokenMenu : public CMenu<unsigned short int>{
    DeckTile* m_deck_tile;
    unsigned short int m_nb_tokens;
public:
    CTokenMenu(NotifiableInterface* tar, DeckTile* decktile, unsigned short int nb_token);
    void show() override;
};

#endif // CTOKENMENU_HPP

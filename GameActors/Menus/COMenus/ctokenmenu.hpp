#ifndef CTOKENMENU_HPP
#define CTOKENMENU_HPP

#include "cmenu.hpp"
#include "../../../Gametools/Abstract/decktile.hpp"
#include "../../player.hpp"


class CTokenMenu : public CMenu<unsigned short int>{
    DeckTile* m_deck_tile;
    Player* const m_caller;
    unsigned short int m_nb_tokens;
public:
    CTokenMenu(NotifiableInterface* tar, DeckTile* decktile, Player* caller);
    ~CTokenMenu() = default;
    void show() override;
};

#endif // CTOKENMENU_HPP

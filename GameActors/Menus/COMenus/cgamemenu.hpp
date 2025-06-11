#ifndef CGAMEMENU_HPP
#define CGAMEMENU_HPP

#include "cmenu.hpp"

class Game;

class CGameMenu : public CMenu<std::tuple<std::string, std::string>> {
public:
    CGameMenu(NotifiableInterface *tar);
    CGameMenu(NotifiableInterface *tar, Game *game);

    void show() override;
private:
    Game *m_game;
};

#endif // CGAMEMENU_HPP

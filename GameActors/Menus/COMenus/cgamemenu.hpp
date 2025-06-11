#ifndef CGAMEMENU_HPP
#define CGAMEMENU_HPP

#include "cmenu.hpp"

class CGameMenu : public CMenu<std::tuple<std::string, std::string>> {
    //Menu utilisé lors du choix des paramètre du jeu
public:
    CGameMenu(NotifiableInterface *tar);
    void show() override;
};

#endif // CGAMEMENU_HPP

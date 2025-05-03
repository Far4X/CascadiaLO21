#ifndef CGAMEMENU_HPP
#define CGAMEMENU_HPP

#include "cmenu.hpp"

class CGameMenu : public CMenu<std::tuple<std::string, std::string>> {
public:
    CGameMenu(NotifiableInterface *tar);
};

#endif // CGAMEMENU_HPP

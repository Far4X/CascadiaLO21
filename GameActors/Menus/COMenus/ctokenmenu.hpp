#ifndef CTOKENMENU_HPP
#define CTOKENMENU_HPP

#include "cmenu.hpp"
class CTokenMenu : public CMenu<std::tuple<GameTile&, const WildlifeToken&>>{
public:
    CTokenMenu();
};

#endif // CTOKENMENU_HPP

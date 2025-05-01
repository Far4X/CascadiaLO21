#ifndef GGAMEMENU_HPP
#define GGAMEMENU_HPP

#include "gmenu.hpp"

class GGameMenu : public GMenu<std::tuple<std::string, std::string>>{
public:
    GGameMenu();
};

#endif // GGAMEMENU_HPP

#ifndef GGAMEMENU_HPP
#define GGAMEMENU_HPP

#include "gmenu.hpp"

class GGameMenu : public GMenu<std::tuple<std::string, std::string>>{
public:
    GGameMenu(NotifiableInterface *tar);
};

#endif // GGAMEMENU_HPP

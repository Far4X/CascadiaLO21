#include "ggamemenu.hpp"

GGameMenu::GGameMenu(NotifiableInterface *tar) : GMenu<std::tuple<std::string, std::string>>(tar) {}

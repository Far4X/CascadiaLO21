#ifndef COPENMENU_HPP
#define COPENMENU_HPP
#include "cmenu.hpp"
#include <string>

class CPlayerMenu : public CMenu<std::string>{
    //Menu utilisé lors du choix des joueurs
    int m_result = 0;
public:
    CPlayerMenu(NotifiableInterface* tar);
    void show() override;
};

#endif // COPENMENU_HPP

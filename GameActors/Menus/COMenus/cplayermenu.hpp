#ifndef COPENMENU_HPP
#define COPENMENU_HPP
#include "cmenu.hpp"
#include <string>

class CPlayerMenu : public CMenu<std::string>{
    int m_result = 0;
public:
    CPlayerMenu();
    void show() override;
};

#endif // COPENMENU_HPP

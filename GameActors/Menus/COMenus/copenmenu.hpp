#ifndef COPENMENU_HPP
#define COPENMENU_HPP
#include "cmenu.hpp"


class COpenMenu : public CMenu{
    int m_result = 0;
public:
    COpenMenu();
    void print() override;
    inline int getResult() const {return m_result;}
};

#endif // COPENMENU_HPP

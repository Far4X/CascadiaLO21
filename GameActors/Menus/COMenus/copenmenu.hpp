#ifndef COPENMENU_HPP
#define COPENMENU_HPP
#include "cmenu.hpp"


class COpenMenu : public CMenu{
    unsigned short m_result = 0;
    std::string m_raw_out;
public:
    COpenMenu();
    void print() const override;
    bool checkResult();
};

#endif // COPENMENU_HPP

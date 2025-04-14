#ifndef CMENU_HPP
#define CMENU_HPP

class CMenu{
    bool m_espect_answer;
public:
    inline CMenu(bool espect_answer = false) : m_espect_answer(espect_answer){};
    virtual void print() = 0;
};

#endif // CMENU_HPP

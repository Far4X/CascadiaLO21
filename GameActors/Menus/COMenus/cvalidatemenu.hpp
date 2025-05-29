#ifndef CVALIDATEMENU_HPP
#define CVALIDATEMENU_HPP

#include "cmenu.hpp"

class CValidateMenu final : public CMenu<bool>{
public:
    CValidateMenu(NotifiableInterface* tar);
    virtual ~CValidateMenu() = default;
    void show() override;
};

#endif // CVALIDATEMENU_HPP

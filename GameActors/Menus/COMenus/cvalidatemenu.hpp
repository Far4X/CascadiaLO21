#ifndef CVALIDATEMENU_HPP
#define CVALIDATEMENU_HPP

#include "cmenu.hpp"

class CValidateMenu final : public CMenu<bool>{
    //Menu utilisé lors du choix de la validation du tour 
public:
    CValidateMenu(NotifiableInterface* tar);
    virtual ~CValidateMenu() = default;
    void show() override;
};

#endif // CVALIDATEMENU_HPP

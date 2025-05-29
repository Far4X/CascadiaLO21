#ifndef SALVABLETHING_HPP
#define SALVABLETHING_HPP
#include <string>

class SalvableThing{
    /*Classe abstraite qui permet l'enregistrement du jeu*/
public:
    SalvableThing();
    virtual ~SalvableThing() = default;
    virtual std::string getSaveString() const = 0;

};

#endif // SALVABLETHING_HPP

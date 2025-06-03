#ifndef SALVABLETHING_HPP
#define SALVABLETHING_HPP
#include <string>
#include <vector>

class SalvableThing{
    /*Classe abstraite qui permet l'enregistrement du jeu*/
public:
    SalvableThing();
    virtual ~SalvableThing() = default;
    virtual std::string getSaveString() const = 0;
    static std::vector<std::string> separateParams(const std::string &raw);
    static unsigned int stringToInt(const std::string &raw);
};

#endif // SALVABLETHING_HPP

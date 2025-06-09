#ifndef SALVABLETHING_HPP
#define SALVABLETHING_HPP
#include <string>
#include <vector>

//{2;2;AAAAA;AA;{Albert;0;{1111;22;222;222}};{}} Exemple de string de sauvegarde

class SalvableThing{
    /*Classe abstraite qui permet l'enregistrement d'un élément du jeu'*/
public:
    SalvableThing();
    virtual ~SalvableThing() = default;
    virtual std::string getSaveString() const = 0;
    static std::vector<std::string> separateParams(const std::string &raw, const char sep = ';');
    static unsigned int stringToInt(const std::string &raw);
};

#endif // SALVABLETHING_HPP

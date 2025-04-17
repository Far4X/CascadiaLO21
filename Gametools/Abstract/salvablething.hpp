#ifndef SALVABLETHING_HPP
#define SALVABLETHING_HPP
#include <string>

/*
Type of saving

{nb_player:2;turn:2;boards:{pid:0,nb_tiles:10,tiles:{...}},{...} }

*/

class SalvableThing{
public:
    SalvableThing();
    virtual ~SalvableThing() = default;
    virtual std::string getSaveString() const = 0;

};

#endif // SALVABLETHING_HPP

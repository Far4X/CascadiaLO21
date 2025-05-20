#include "cmenu.hpp"
#include "../../../Gametools/Tiling/gametile.hpp"

template <typename T>
CMenu<T>::CMenu(NotifiableInterface* tar) : Menu<T>(tar){

}


template class CMenu<std::string>;
template class CMenu<std::tuple<std::string, std::string>>;
template class CMenu<std::tuple<GameTile&, const WildlifeToken&>>;

#include "gdecktile.hpp"

GDeckTile::GDeckTile() {}


GDeckTile& GDeckTile::getInstance(){
    static GDeckTile ins;
    return ins;
}

std::string GDeckTile::getSaveString() const {
    return "";
}

void GDeckTile::show(){

}

#include "gdecktile.hpp"

GDeckTile::GDeckTile() {}


GDeckTile& GDeckTile::getInstance(){
    static GDeckTile ins;
    return ins;
}

void GDeckTile::show(){

}

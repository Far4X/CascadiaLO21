#include "gdecktile.hpp"
#include <iostream>

GDeckTile::GDeckTile() {}


GDeckTile& GDeckTile::getInstance(){
    static GDeckTile ins;
    return ins;
}

std::string GDeckTile::getSaveString() const {
    return "";
}

void GDeckTile::construct(){
    if(widget != nullptr) delete widget;
    widget = new QWidget;
    deck = new QVBoxLayout(widget);
    for(int i = 0; i<4;i++)
    {
        const GameTile* tile = getTile(i);
        if (tile == nullptr){
            throw CustomError("Tile doesn't exists", 999);
        }
        QLabel* label = new QLabel(widget);
        QPixmap pixmap = PixmapFactory::createTile(tile);
        //QPixmap token(PixmapFactory::matchToken(m_token))
        label->setPixmap(pixmap);
        label->setFixedSize(64, 55);
        label->setScaledContents(true);  // Pour que l'image remplisse le QLabel
        deck->addWidget(label,i);
    }

}

void GDeckTile::show(){
    std::cout<<"k";
    construct();
    GraphXVue::instance()->addDeck(widget);
    widget->show();
    std::cout<<"ok";

}

#include "gtile.hpp"
#include <Qt>
#include <iostream>


QPixmap PixmapFactory::createIconWithOverlay(const QString& basePath, const QString& token1,const QString& token2,const QString& token3) {
    QPixmap base(basePath);
    QPixmap overlay1(token1);
    QPixmap overlay2(token2);
    QPixmap overlay3(token3);
    if(!overlay1.isNull()){
    overlay1 = overlay1.scaled(
        overlay1.width() * 0.8,
        overlay1.height() * 0.8,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
            );}
    if(!overlay2.isNull()){
    overlay2 = overlay2.scaled(
        overlay2.width() * 0.8,
        overlay2.height() * 0.8,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );}
    if(!overlay3.isNull()){
    overlay3 = overlay3.scaled(
        overlay3.width() * 0.8,
        overlay3.height() * 0.8,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );}

    QPixmap result(base.size());
    result.fill(Qt::transparent);

    QPainter painter(&result);
    painter.drawPixmap(0, 0, base);
    painter.drawPixmap(30, 0, overlay1);
    painter.drawPixmap(10, 30, overlay2);
    painter.drawPixmap(50, 30, overlay3);
    painter.end();

    return result;
}

QString PixmapFactory::matchTile(GameTile* tile){
    if(tile == nullptr)
    {
        return ":/Assets/Assets/tileOutline.png";
    }
    else{
        return ":/Assets/Assets/Tiles/desert.png";
    }
}

QString PixmapFactory::matchToken(GameTile* tile,int token){
    if(tile == nullptr)
    {
        return "";
    }
    if(tile->getToken() == nullptr)
    {
        if(tile->getWildlife(token) == Bear)
        {
            return ":/Token/Assets/Token/bear.png";
        }
        if(tile->getWildlife(token) == Fox)
        {
            return ":/Token/Assets/Token/fox.png";
        }
        if(tile->getWildlife(token) == Elk)
        {
            return ":/Token/Assets/Token/elk.png";
        }
        if(tile->getWildlife(token) == Hawk)
        {
            return ":/Token/Assets/Token/hawk.png";
        }
        if(tile->getWildlife(token) == Salmon)
        {
            return ":/Token/Assets/Token/salmon.png";
        }
    }
    if(tile->getToken()->getWildlifeType() == Bear)
    {
        return ":/Token/Assets/Token/bearActive.png";
    }
    if(tile->getToken()->getWildlifeType() == Fox)
    {
        return ":/Token/Assets/Token/foxActive.png";
    }
    if(tile->getToken()->getWildlifeType() == Elk)
    {
        return ":/Token/Assets/Token/elkActive.png";
    }
    if(tile->getToken()->getWildlifeType() == Hawk)
    {
        return ":/Token/Assets/Token/hawkActive.png";
    }
    if(tile->getToken()->getWildlifeType() == Salmon)
    {
        return ":/Token/Assets/Token/salmonActive.png";
    }
    else{
        std::cout << "Token not found"<<std::endl;
        return "";
    }

}

QPixmap PixmapFactory::createTile(GameTile* tile){
    int nbtoken = 1;
    const WildlifeToken* token;
    if (tile!=nullptr)
    {
        nbtoken = tile->getNbWildlife();
        token = tile->getToken();
    }
    if (nbtoken == 1 || token!=nullptr){
        return createIconWithOverlay(matchTile(tile),matchToken(tile,0));
    }
    if (nbtoken == 2){
       return createIconWithOverlay(matchTile(tile),matchToken(tile,0),matchToken(tile,1));
    }
    if (nbtoken == 3){
       return createIconWithOverlay(matchTile(tile),matchToken(tile,0),matchToken(tile,1),matchToken(tile,2));
    }
    return QPixmap();
}

#include "gtile.hpp"
#include <Qt>
#include <iostream>

QPixmap PixmapFactory::createIconWithOverlay(const QString& basePath, const QString& token1, int rot,const QString& token2,const QString& token3) {
    QPixmap base(basePath);
    QPixmap overlay1(token1);
    QPixmap overlay2(token2);
    QPixmap overlay3(token3);

    if (rot != 0) {
        QTransform transform;
        transform.rotate(rot * 60);
        base = base.transformed(transform, Qt::SmoothTransformation);
        std::cout<<"ROTATION : "<<rot<<std::endl;
    }

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
    if(rot == 0 || rot == 3){
    painter.drawPixmap(35, 10, overlay1);
    painter.drawPixmap(15, 45, overlay2);
    painter.drawPixmap(55, 45, overlay3);
    }
    else{
        int rotoffset = 20; // la rotation implique un zoom
        painter.drawPixmap(35+rotoffset, 10+rotoffset, overlay1);
        painter.drawPixmap(15+rotoffset, 45+rotoffset, overlay2);
        painter.drawPixmap(55+rotoffset, 45+rotoffset, overlay3);
    }
    painter.end();

    return result;
}

QString PixmapFactory::matchTile(const GameTile* tile){
    int desert = 0;
    int lake = 0;
    int montains = 0;
    int swamp = 0;
    int forest = 0;
    if(tile == nullptr)
    {
        return ":/Assets/Assets/tileOutline.png";
    }

    // Stock les infos d'une tuile
    for (int i = 0; i<6; i++){
        if(tile->getBiome(i) == Prairie) desert++;
        if(tile->getBiome(i) == River) lake++;
        if(tile->getBiome(i) == Wetland) swamp++;
        if(tile->getBiome(i) == Mountain) montains++;
        if(tile->getBiome(i) == Forest) forest++;
    }

    // Desert :
    if(desert == 6) return ":/Assets/Assets/Tiles/desert.png";
    if(desert == 3){
        if(lake == 3) return ":/Tile/Assets/Tiles/desert+lake.png";
        if(swamp == 3) return ":/Tile/Assets/Tiles/desert+swamp.png";
    }

    // Lake :
    if(lake == 6) return ":/Assets/Assets/Tiles/lake.png";
    if(lake == 3 && montains == 3) return ":/Tile/Assets/Tiles/lake+mountain.png";

    // Montains :
    if(montains == 6) return ":/Tile/Assets/Tiles/mountain.png";
    if(montains == 3){
        if(desert == 3) return ":/Tile/Assets/Tiles/mountain+desert.png";
        if(forest == 3) return ":/Tile/Assets/Tiles/mountain+forest.png";
        if(swamp == 3) return ":/Tile/Assets/Tiles/mountain+swamp.png";
    }

    // Swamp :
    if(swamp == 6) return ":/Tile/Assets/Tiles/swamp.png";
    if(swamp == 3 && lake == 3) return ":/Tile/Assets/Tiles/swamp+lake.png";

    // Forest :
    if(forest == 6) return ":/Tile/Assets/Tiles/forest.png";
    if(forest == 3){
        if(desert == 3) return ":/Tile/Assets/Tiles/forest+desert.png";
        if(lake == 3) return ":/Tile/Assets/Tiles/forest+lake.png";
        if(swamp == 3) return ":/Tile/Assets/Tiles/forest+swamp.png";
    }
    std::cout<<"doesn't match"<<std::endl;
    std::cout<<"Desert : "<<desert<<" Lake : "<<lake<<" Montains : "<<montains<<" Swamp : "<<swamp<<" Forest : "<<forest<<std::endl;
    return ":/Assets/Assets/Tiles/desert.png";

}

QString PixmapFactory::matchToken(Wildlife wild){
    if(wild == Bear)
    {
        return ":/Token/Assets/Token/bear.png";
    }
    if(wild == Fox)
    {
        return ":/Token/Assets/Token/fox.png";
    }
    if(wild == Elk)
    {
        return ":/Token/Assets/Token/elk.png";
    }
    if(wild == Hawk)
    {
        return ":/Token/Assets/Token/hawk.png";
    }
    if(wild == Salmon)
    {
        return ":/Token/Assets/Token/salmon.png";
    }
    return "";
}

QString PixmapFactory::matchToken(const GameTile* tile,int token){
    if(tile == nullptr)
    {
        return "";
    }
    if(tile->getToken() == nullptr)
    {
        return matchToken(tile->getWildlife(token));
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


QPixmap PixmapFactory::createTile(const GameTile* tile){
    int nbtoken = 1;
    const WildlifeToken* token;
    if (tile!=nullptr)
    {
        nbtoken = tile->getNbWildlife();
        token = tile->getToken();
    }
    if (nbtoken == 1 || token!=nullptr){
        return createIconWithOverlay(
            matchTile(tile),
            matchToken(tile,0),
            tile ? tile->getRotation() : 0);
    }
    if (nbtoken == 2){
       return createIconWithOverlay(
            matchTile(tile),
            matchToken(tile,0),
            tile ? tile->getRotation() : 0,matchToken(tile,1));
    }
    if (nbtoken == 3){
       return createIconWithOverlay(
            matchTile(tile),
            matchToken(tile,0),
            tile ? tile->getRotation() : 0,matchToken(tile,1),matchToken(tile,2));
    }
    return QPixmap();
}

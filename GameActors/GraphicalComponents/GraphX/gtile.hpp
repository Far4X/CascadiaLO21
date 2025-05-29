#ifndef GTILE_HPP
#define GTILE_HPP

#include <QPainter>
#include "Gametools/Tiling/gametile.hpp"

class PixmapFactory
{
public:
    PixmapFactory() = delete;
    static QPixmap createTile(GameTile* tile);
private:
    static QPixmap createIconWithOverlay(const QString& basePath, const QString& token1,const QString& token2= QString(),const QString& token3= QString());
    static QString matchTile(GameTile* tile);
    static QString matchToken(GameTile* tile, int token);

};

#endif // GTILE_H

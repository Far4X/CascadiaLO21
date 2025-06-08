#ifndef GTILE_HPP
#define GTILE_HPP

#include <QPainter>
#include "Gametools/Tiling/gametile.hpp"

class PixmapFactory
{
public:
    PixmapFactory() = delete;
    static QPixmap createTile(const GameTile* tile);
    static QString matchToken(Wildlife wild);
private:
    static QPixmap createIconWithOverlay(const QString& basePath, const QString& token1,int rot = 0,const QString& token2= QString(),const QString& token3= QString());
    static QString matchTile(const GameTile* tile);
    static QString matchToken(const GameTile* tile, int token);
};

#endif // GTILE_H

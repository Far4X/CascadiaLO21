#ifndef GDECKCARD_HPP
#define GDECKCARD_HPP
#include "../../../Gametools/Abstract/decktile.hpp"
#include "gtile.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include "graphxvue.hpp"
#include "glabel.hpp"
#include <QObject>

// Plus tard je mettrai tout dans la factory, je ferai une Label Factory

class GDeckTile : public QObject, public DeckTile{
    Q_OBJECT
private:
    GDeckTile(QObject *parent = nullptr);
    void construct();

    GDeckTile(const GDeckTile &tar) = delete;
    GDeckTile &operator=(const GDeckTile &tar) = delete;
    ~GDeckTile() = default;

    QVBoxLayout* tiles;
    QVBoxLayout* tokens;
    QHBoxLayout* deck;
    QWidget* widget;

    // On a besoin de chaque pointeur pour update l'affichage sans tout reconstruire.

    ClickableLabel* ti1 = nullptr;
    ClickableLabel* ti2 = nullptr;
    ClickableLabel* ti3 = nullptr;
    ClickableLabel* ti4 = nullptr;
    std::vector<ClickableLabel*> tilesL;

    ClickableLabel* to1 = nullptr;
    ClickableLabel* to2 = nullptr;
    ClickableLabel* to3 = nullptr;
    ClickableLabel* to4 = nullptr;
    std::vector<ClickableLabel*> tokenL;

signals:
    void tileClicked(int index);
    void tokenClicked(int index);

public:

    void update();
    void show() override;
    static GDeckTile& getInstance();

};

#endif // GDECKCARD_HPP

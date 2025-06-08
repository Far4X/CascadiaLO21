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

    GDeckTile(const GDeckTile &tar) = delete;
    GDeckTile &operator=(const GDeckTile &tar) = delete;
    ~GDeckTile() = default;
    void construct();
    QVBoxLayout* tiles;
    QVBoxLayout* tokens;
    QHBoxLayout* deck;
    QWidget* widget;

signals:
    void tileClicked(int index);

public:
    void show() override;
    static GDeckTile& getInstance();

};

#endif // GDECKCARD_HPP

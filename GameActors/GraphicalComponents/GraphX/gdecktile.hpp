#ifndef GDECKCARD_HPP
#define GDECKCARD_HPP
#include "../../../Gametools/Abstract/decktile.hpp"
#include "gtile.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include "graphxvue.hpp"

// Plus tard je mettrai tout dans la factory, je ferai une Label Factory

class GDeckTile : public DeckTile{
private:
    GDeckTile();

    GDeckTile(const GDeckTile &tar) = delete;
    GDeckTile &operator=(const GDeckTile &tar) = delete;
    ~GDeckTile() = default;
    void construct();
    QVBoxLayout* tiles;
    QVBoxLayout* tokens;
    QHBoxLayout* deck;
    QWidget* widget;

public:
    void show() override;
    static GDeckTile& getInstance();

    std::string getSaveString() const override;
};

#endif // GDECKCARD_HPP

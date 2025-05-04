#ifndef WIDGETHEXBOARD_H
#define WIDGETHEXBOARD_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
//#include <QMouseEvent>

    const int tileWidth = 64;  // Largeur de la tuile hexagonale
const int tileHeight = 64; // Hauteur de la tuile hexagonale
const int xOffset = tileWidth * 3 / 4; // Décalage horizontal entre les tuiles
const int yOffset = tileHeight / 2;    // Décalage vertical pour les lignes impaires

class WidgetHexBoard : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetHexBoard(QWidget *parent = nullptr,int size = 41);
    ~WidgetHexBoard() = default;

    // Méthode pour initialiser les tuiles (à appeler dans le constructeur)
    void initHexTiles();
protected:
    //void mousePressEvent(QMouseEvent *event) override; // Surcharge pour capter les clics

private:
    int max_size;
    QVBoxLayout* m_layout; // Layout principal pour l'organisation du contenu

signals:
};

#endif // WIDGETHEXBOARD_H

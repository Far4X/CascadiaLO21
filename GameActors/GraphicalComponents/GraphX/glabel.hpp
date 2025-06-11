#ifndef GLABEL_HPP
#define GLABEL_HPP

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

/*On n'utilise pas cette class dans gplayerboard car les label sont des carrés, cependant :
*En developpement (et si on a le temps de finir cette fonctionnalitée) il serait utile d'utiliser cette class dans gplayerboard puis de check la distance
*au centre de notre tuile, ainsi on pourrait savoir si on est dans la bonne ou pas. Il y aurait toujours des soucis mais cette fois en dehors du cercle ainsi
*la fonctionnalité est relégué au second plan.
*/

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }
        QLabel::mousePressEvent(event);
    }
};
#endif // GLABEL_HPP

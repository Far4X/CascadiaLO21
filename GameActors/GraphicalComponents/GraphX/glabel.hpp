#ifndef GLABEL_HPP
#define GLABEL_HPP

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

//On n'utilise pas cette class dans gplayerboard car les label sont des carrés


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

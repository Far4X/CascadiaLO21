#ifndef GRAPHXVUE_H
#define GRAPHXVUE_H


#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QGraphicsScene>
#include <QTabBar>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <vector>
#include <QMouseEvent>


class GPlayerBoard;


class GraphXView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphXView(QGraphicsScene* scene, QWidget* parent = nullptr)
        : QGraphicsView(scene, parent) {}

signals:
    void rightClickAt(const QPointF& scenePos);

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::RightButton) {
            QPointF scenePos = mapToScene(event->pos());
            emit rightClickAt(scenePos);
            event->accept();
            return; // on stoppe ici
        }
        QGraphicsView::mousePressEvent(event); // sinon comportement normal
    }

    void wheelEvent(QWheelEvent *event) override
    {
        const double scaleFactor = 1.15;

        double currentScale = transform().m11();  // suppose uniform scale
        if (currentScale < 0.1 && event->angleDelta().y() < 0)
            return; // trop petit
        if (currentScale > 10.0 && event->angleDelta().y() > 0)
            return; // trop gros

        if (event->angleDelta().y() > 0) {
            // Zoom in
            scale(scaleFactor, scaleFactor);
        } else {
            // Zoom out
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
        event->accept();
    }
};


class GraphXVue : public QObject
{
    Q_OBJECT
public:
    static GraphXVue* instance();

    void addPlayerBoard(GPlayerBoard* board);
    inline void setCurrentPlayuer(int current){currentboard = current;}
    void show(int playerIndex = 0);
    QWidget* getWindow(){return m_window;}
    QGraphicsScene* getScene() const { return m_scene; }
    void addMenu(QWidget* menu);
    void addDeck(QWidget* deck);
    void nextTurn();

private slots:
    void onTabChanged(int index);

signals:
    void rightClickOnBoard(GPlayerBoard* board, const QPointF& pos);

private:
    explicit GraphXVue(QObject *parent = nullptr);
    static GraphXVue* s_instance;

    //Fenetre principal :
    QWidget* m_window;
    QHBoxLayout* m_main_layout;

    //left pannel de la fenetre
    QWidget* m_left_panel; // la pioche
    QVBoxLayout* m_left_panel_layout; //

    int m_turn_count = 20;
    QLCDNumber* m_lcd;  // nombre de tours

    //right pannel
    QWidget* m_right_panel;
    QVBoxLayout* m_right_panel_layout; //

    //rightPanel :
    QTabBar* m_onglet;
    GraphXView* m_view; // la vue les gplayerboard
    QGraphicsScene* m_scene; // la scene

    int currentboard;
    std::vector<GPlayerBoard*> boards;
    QGraphicsProxyWidget* proxy;
    std::vector<QGraphicsProxyWidget*> proxies;

    //detection :

    bool isPointInHex(QPointF point, QPointF center, float radius) {
        QPolygonF hex;
        for (int i = 0; i < 6; ++i) {
            float angle_deg = 60 * i - 30;  // flat-topped
            float angle_rad = M_PI / 180.0 * angle_deg;
            hex << QPointF(center.x() + radius * std::cos(angle_rad),
                           center.y() + radius * std::sin(angle_rad));
        }
        return hex.containsPoint(point, Qt::OddEvenFill);
    }

    void onRightClickAt(const QPointF& scenePos);

};

#endif // GRAPHXVUE_H

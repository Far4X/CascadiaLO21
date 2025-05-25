#ifndef GRAPHXVUE_H
#define GRAPHXVUE_H


#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
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
            // Ne pas appeler la base ici pour éviter propagation?
            // Ou appeller si tu veux permettre d'autres handlers ?
            event->accept();
            return; // on stoppe ici
        }
        QGraphicsView::mousePressEvent(event); // sinon comportement normal
    }
};


class GraphXVue : public QObject
{
    Q_OBJECT
public:
    static GraphXVue* instance();

    void addPlayerBoard(GPlayerBoard* board);
    void show();
    QWidget* getWindow(){return m_window;}
    QGraphicsScene* getScene() const { return m_scene; }
    void addMenu(QWidget* menu);

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


    void onRightClickAt(const QPointF& scenePos);

};

#endif // GRAPHXVUE_H

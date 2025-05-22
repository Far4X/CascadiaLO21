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

class GPlayerBoard;


class GraphXVue : public QObject
{
    Q_OBJECT
public:
    static GraphXVue* instance();

    void addPlayerBoard(GPlayerBoard* board);
    void show();

private slots:
    void onTabChanged(int index);

private:
    explicit GraphXVue(QObject *parent = nullptr);
    static GraphXVue* s_instance;

    //Fenetre principal :
    QWidget* m_window;
    QHBoxLayout* m_main_layout;

    //left pannel de la fenetre
    QWidget* m_left_panel; // la pioche

    //right pannel
    QWidget* m_right_panel;
    QVBoxLayout* m_right_panel_layout; //

    //rightPanel :
    QTabBar* m_onglet;
    QGraphicsView* m_view; // la vue les gplayerboard
    QGraphicsScene* m_scene; // la scene




    std::vector<GPlayerBoard*> boards;
    QGraphicsProxyWidget* proxy;
    std::vector<QGraphicsProxyWidget*> proxies;
};

#endif // GRAPHXVUE_H

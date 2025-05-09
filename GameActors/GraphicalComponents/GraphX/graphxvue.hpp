#ifndef GRAPHXVUE_H
#define GRAPHXVUE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

class GPlayerBoard;


class GraphXVue : public QObject
{
    Q_OBJECT
public:
    static GraphXVue* instance();

    void addPlayerBoard(GPlayerBoard* board);
    void show();

private:
    explicit GraphXVue(QObject *parent = nullptr);
    static GraphXVue* s_instance;
    QWidget* m_window;
    QVBoxLayout* m_layout;

signals:
};

#endif // GRAPHXVUE_H

#ifndef GPLAYERBOARD_HPP
#define GPLAYERBOARD_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "Gametools/Abstract/playerboard.hpp"

class GPlayerBoard : public PlayerBoard{
public:
    GPlayerBoard();
    ~GPlayerBoard();
    QWidget* getWidget() const;
    void show() override;
private:
    QWidget* m_widget;
    QGridLayout* m_layout;  // Layout pour organiser les widgets
    QPushButton* m_btn_quit;  // Exemple de bouton
    QLabel* m_label;  // Exemple de label
};

#endif // GPLAYERBOARD_HPP

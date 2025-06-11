#ifndef GPLAYERMENU_HPP
#define GPLAYERMENU_HPP

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

#include "gmenu.hpp"

class GPlayerMenu : public GMenu<std::string>{
    QGridLayout* m_main_layout = nullptr;

    QPushButton* m_btn_quit = nullptr;
    QPushButton* m_btn_validate = nullptr;
    QLabel* m_label = nullptr;

    QSpinBox* m_spinbox = nullptr;
    QLineEdit** m_lines_names = nullptr;
    QLabel** m_label_names = nullptr;


    unsigned short m_nb_player = 0;
public:
    GPlayerMenu(NotifiableInterface* tar);
    ~GPlayerMenu();
    void validateNumber();
    void validateNames();
    void show() override;
};

#endif // GPLAYERMENU_HPP

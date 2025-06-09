#ifndef GGAMEMENU_HPP
#define GGAMEMENU_HPP

#include "gmenu.hpp"

#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


class GGameMenu : public GMenu<std::tuple<std::string, std::string>>{
    /*Classe qui gère le menu au démarrage du*/
    Q_OBJECT
    QGridLayout* m_main_layout = nullptr;
    QLabel* m_label = nullptr;
    QLabel* m_label_exp_recover = nullptr;
    QLabel* m_label_exp_variant = nullptr;
    QLabel* m_label_exp_use_variant = nullptr;
    QLabel* m_label_exp_cards = nullptr;

    QPushButton* m_btn_recover = nullptr;
    QPushButton* m_btn_use_variant = nullptr;
    QPushButton* m_btn_validate = nullptr;

    QLineEdit* m_line_edit_cards = nullptr;
    QLineEdit* m_line_edit_variant = nullptr;
public:
    GGameMenu(NotifiableInterface *tar);
    void show() override;
    void validate();
    void usePreviousGame();
    void useVariant();
};

#endif // GGAMEMENU_HPP

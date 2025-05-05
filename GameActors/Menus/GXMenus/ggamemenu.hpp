#ifndef GGAMEMENU_HPP
#define GGAMEMENU_HPP

#include "gmenu.hpp"

#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


class GGameMenu : public GMenu<std::tuple<std::string, std::string>>{
    Q_OBJECT
    QGridLayout* m_main_layout = nullptr;
    QLabel* m_label = nullptr;
    QLabel* m_label_exp_recover = nullptr;
    QLabel* m_label_exp_load_extension = nullptr;
    QLabel* m_label_exp_cards = nullptr;

    QPushButton* m_btn_recover = nullptr;
    QPushButton* m_btn_load_extension = nullptr;
    QPushButton* m_btn_validate = nullptr;

    QPushButton* m_btn_restart = nullptr;
    QPushButton* m_btn_quit = nullptr;

    QLineEdit* m_line_edit_cards = nullptr;
public:
    GGameMenu(NotifiableInterface *tar);
    void show() override;
    void validate();
    void usePreviousGame();
    void loadExtension();
    void quitGame();
    void restartGame();

};

#endif // GGAMEMENU_HPP

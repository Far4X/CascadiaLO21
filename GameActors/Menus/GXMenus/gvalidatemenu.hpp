#ifndef GVALIDATEMENU_HPP
#define GVALIDATEMENU_HPP
#include "gmenu.hpp"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>


class GValidateMenu final : public GMenu<bool>{
    QLabel* m_label = nullptr;
    QGridLayout* m_layout = nullptr;
    QPushButton* m_btn_validate = nullptr;
    QPushButton *m_btn_reject = nullptr;

public:
    GValidateMenu(NotifiableInterface* tar);
    ~GValidateMenu();
    void show() override;
    void validate();
    void reject();
};
#endif // GVALIDATEMENU_HPP

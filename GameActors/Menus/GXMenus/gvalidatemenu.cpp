#include "gvalidatemenu.hpp"

GValidateMenu::GValidateMenu(NotifiableInterface* tar) : GMenu(tar) {
    m_label = new QLabel("Voulez-vous valider les actions réalisées ?", this);
    m_layout = new QGridLayout(this);
    m_btn_validate = new QPushButton("Valider", this);
    m_btn_reject = new QPushButton("Rejeter", this);

    m_layout->addWidget(m_label, 0, 0, 1, 2);
    m_layout->addWidget(m_label, 1, 0, 1, 1);
    m_layout->addWidget(m_label, 1, 2, 1, 1);

    QObject::connect(m_btn_validate, &QPushButton::clicked, this, &GValidateMenu::validate);
    QObject::connect(m_btn_reject, &QPushButton::clicked, this, &GValidateMenu::reject);
}

void GValidateMenu::show(){
    return QWidget::show();
}

GValidateMenu::~GValidateMenu(){

}

void GValidateMenu::validate(){
    addResult(true);
    m_target->notifyInterface(5);
}

void GValidateMenu::reject(){
    addResult(false);
    m_target->notifyInterface(5);
}

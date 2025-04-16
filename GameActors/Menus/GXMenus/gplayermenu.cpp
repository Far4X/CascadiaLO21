#include "gplayermenu.hpp"

GPlayerMenu::GPlayerMenu(NotifiableInterface* tar) : GMenu(tar, nullptr, 300, 200, 200, 200){
    m_main_layout = new QGridLayout(this);

    m_btn_quit = new QPushButton(QString("Quitter") ,this);
    m_btn_validate = new QPushButton(QString("Valider"), this);
    m_spinbox = new QSpinBox(this);
    m_label = new QLabel(QString("Merci de choisr le nombre de joueurs : "), this);

    m_spinbox->setMaximum(4);
    m_spinbox->setMinimum(1);

    m_main_layout->addWidget(m_label, 0, 0, 1, 2);
    m_label->setGeometry(600, 100, 0, 0);

    m_main_layout->addWidget(m_spinbox, 1, 0, 1, 2);
    m_main_layout->addWidget(m_btn_quit, 2, 1, 1, 1);
    m_main_layout->addWidget(m_btn_validate, 2, 0, 1, 1);


    QObject::connect(m_btn_quit, &QPushButton::clicked, this, &QWidget::hide);
    QObject::connect(m_btn_validate, &QPushButton::clicked, this, &GPlayerMenu::validateNumber);
}

GPlayerMenu::~GPlayerMenu(){
    delete m_main_layout;
    delete m_btn_quit;
    delete m_btn_validate;
    delete m_label;
    delete m_spinbox;

    for (int i = 0; i < m_nb_player; i++){
        delete m_lines_names[i];
        delete m_label_names[i];
    }
    delete[] m_lines_names;
    delete[] m_label_names;

    m_main_layout = nullptr;
    m_btn_quit = nullptr;
    m_btn_validate = nullptr;
    m_label= nullptr;
    m_spinbox = nullptr;
    m_lines_names = nullptr;
    m_label_names = nullptr;
}

void GPlayerMenu::validateNumber(){
    m_label->setText("Validé !");
}

void GPlayerMenu::validateNames(){
    this->hide();
    m_target->notify(1);
}

void GPlayerMenu::show(){
    QWidget::show();
}

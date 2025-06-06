#include "ggamemenu.hpp"

GGameMenu::GGameMenu(NotifiableInterface *tar) : GMenu<std::tuple<std::string, std::string>>(tar, nullptr, 300, 200, 200, 200){
    m_main_layout = new QGridLayout(this);

    m_label = new QLabel(QString("Veuillez choisir les options de la partie: "), this);
    m_label_exp_recover = new QLabel(QString("Appuyer ici pour récupérer la partie précédente : "), this);
    m_label_exp_variant = new QLabel(QString("Entrez ici la variante à utiliser (I ou F) : "), this);
    m_label_exp_use_variant = new QLabel(QString("Appuyer ici pour utiliser une variante : "), this);
    m_label_exp_cards = new QLabel(QString("Entrez ici la suite des cartes à utiliser pour le décomptage des points. Merci de mettre dans l'ordre suivant : Ours, Elan, Aigle, Renard, Saumon (ex : ABCDA)"), this);

    m_btn_recover = new QPushButton(QString("Récupérer"), this);
    m_btn_use_variant = new QPushButton(QString("Utiliser la variante"), this);
    m_btn_validate = new QPushButton(QString("Valider"), this);


    //m_btn_restart = new QPushButton(QString("Recommencer"), this);
    //m_btn_quit = new QPushButton(QString("Quitter"), this);


    m_line_edit_cards = new QLineEdit(QString("AAAAA"), this);
    m_line_edit_variant = new QLineEdit(QString("F"), this);

    m_main_layout->addWidget(m_label, 0, 0, 1, 4);

    m_main_layout->addWidget(m_label_exp_recover, 1, 0, 1, 1);
    m_main_layout->addWidget(m_btn_recover, 1, 1, 1, 1);

    m_main_layout->addWidget(m_label_exp_variant, 2, 0, 1, 1);
    m_main_layout->addWidget(m_line_edit_variant, 2, 1, 1, 1);

    m_main_layout->addWidget(m_label_exp_use_variant, 3, 0, 1, 1);
    m_main_layout->addWidget(m_btn_use_variant, 3, 1, 1, 1);

    m_main_layout->addWidget(m_label_exp_cards, 4, 0, 1, 1);
    m_main_layout->addWidget(m_line_edit_cards, 4, 1, 1, 1);

    m_main_layout->addWidget(m_btn_validate, 5, 1, 1, 1);

    //m_main_layout->addWidget(m_btn_restart, 5, 0, 1, 1);
    //m_main_layout->addWidget(m_btn_quit, 5, 1, 1, 1);

    QObject::connect(m_btn_validate, &QPushButton::clicked, this, &GGameMenu::validate);
    QObject::connect(m_btn_use_variant, &QPushButton::clicked, this, &GGameMenu::useVariant);
    QObject::connect(m_btn_recover, &QPushButton::clicked, this, &GGameMenu::usePreviousGame);
    //QObject::connect(m_btn_restart, &QPushButton::clicked, this, &GGameMenu::restartGame);
    //QObject::connect(m_btn_quit, &QPushButton::clicked, this, &GGameMenu::quitGame);


}

void GGameMenu::validate(){
    this->addResult(std::tuple<std::string, std::string>("Use cards", m_line_edit_cards->text().toStdString()));
    this->hide();
    if (m_target != nullptr){
        m_target->notifyInterface(2);
    }
}
void GGameMenu::usePreviousGame(){
    this->addResult(std::tuple<std::string, std::string>("Recover", "true"));
    this->hide();
    if (m_target != nullptr){
        m_target->notifyInterface(2);
    }
}
void GGameMenu::useVariant(){
    this->addResult(std::tuple<std::string, std::string>("Use variant", m_line_edit_variant->text().toStdString()));
    this->hide();
    if (m_target != nullptr){
        m_target->notifyInterface(2);
    }
}


/*void GGameMenu::restartGame(){
    this->addResult(std::tuple<std::string, std::string>("Restart", "true"));
    this->hide();
    if (m_target != nullptr){
        m_target->notify(2);
    }
}
void GGameMenu::quitGame(){
    this->addResult(std::tuple<std::string, std::string>("Quit", "true"));
    this->hide();
    if (m_target != nullptr){
        m_target->notify(2);
    }
}*/

void GGameMenu::show(){
    QWidget::show();
}

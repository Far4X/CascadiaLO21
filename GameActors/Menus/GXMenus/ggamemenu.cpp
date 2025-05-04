#include "ggamemenu.hpp"

GGameMenu::GGameMenu(NotifiableInterface *tar) : GMenu<std::tuple<std::string, std::string>>(tar, nullptr, 300, 200, 200, 200){
    m_main_layout = new QGridLayout(this);

    m_label = new QLabel(QString("Veuillez choisir les options de la partie: "), this);
    m_label_exp_recover = new QLabel(QString("Appuyer ici pour récupérer la partie précédente : "), this);
    m_label_exp_load_extension = new QLabel(QString("Appuyer ici pour charger l'exentsion : "), this);
    m_label_exp_cards = new QLabel(QString("Entrez ici la suite des cartes à utiliser pour le décomptage des ppints. Merci de mettre dans l'ordre suivant : Ours, Elan, Aigle, Renard, Saumon (ex : ABCDA)"), this);

    m_btn_recover = new QPushButton(QString("Récupérer"), this);
    m_btn_load_extension = new QPushButton(QString("Charger l'extension"), this);
    m_btn_validate = new QPushButton(QString("Valider"), this);

    m_line_edit_cards = new QLineEdit(QString("AAAAA"), this);

    m_main_layout->addWidget(m_label, 0, 0, 1, 2);

    m_main_layout->addWidget(m_label_exp_recover, 1, 0, 1, 1);
    m_main_layout->addWidget(m_btn_recover, 1, 1, 1, 1);

    m_main_layout->addWidget(m_label_exp_load_extension, 2, 0, 1, 1);
    m_main_layout->addWidget(m_btn_load_extension, 2, 1, 1, 1);

    m_main_layout->addWidget(m_label_exp_cards, 3, 0, 1, 1);
    m_main_layout->addWidget(m_line_edit_cards, 3, 1, 1, 1);

    m_main_layout->addWidget(m_btn_validate, 4, 1, 1, 1);

    QObject::connect(m_btn_validate, &QPushButton::clicked, this, &GGameMenu::validate);
    QObject::connect(m_btn_load_extension, &QPushButton::clicked, this, &GGameMenu::loadExtension);
    QObject::connect(m_btn_recover, &QPushButton::clicked, this, &GGameMenu::usePreviousGame);

}

void GGameMenu::validate(){
    this->addResult(std::tuple<std::string, std::string>("Use cards", m_line_edit_cards->text().toStdString()));
    this->hide();
    if (m_target != nullptr){
        m_target->notify(2);
    }
}
void GGameMenu::usePreviousGame(){
    this->addResult(std::tuple<std::string, std::string>("Recover", "true"));
    this->hide();
    if (m_target != nullptr){
        m_target->notify(2);
    }
}
void GGameMenu::loadExtension(){
    this->addResult(std::tuple<std::string, std::string>("Load extension", "true"));
    QObject::disconnect(m_btn_recover, &QPushButton::clicked, this, &GGameMenu::usePreviousGame);
    m_btn_recover->hide();
}


void GGameMenu::show(){
    QWidget::show();
}

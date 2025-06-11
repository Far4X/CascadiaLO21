#include "gtokenmenu.hpp"
#include <iostream>

GTokenMenu::GTokenMenu(NotifiableInterface* tar,DeckTile* decktile, Player *caller) : GMenu(tar, nullptr, 300, 200, 200, 200), m_caller(caller){
    m_main_layout = new QGridLayout(this);
    m_btn_clear_tokens  = new QPushButton("Regénérer les tokens", this);
    m_btn_no_token = new QPushButton("Ne pas utiliser de token", this);;
    m_btn_multichoice = new QPushButton("Choisir séparément token et tuile", this);
    std::string str = "Vous avez " + std::to_string(m_caller->getNbNatureToken()) + " Tokens";
    m_label = new QLabel(str.c_str(), this);

    m_decktile = decktile;

    m_main_layout->addWidget(m_label, 0, 0, 1, 3);
    m_main_layout->addWidget(m_btn_clear_tokens, 1, 1, 1, 1);
    m_main_layout->addWidget(m_btn_no_token, 1, 0, 1, 1);
    m_main_layout->addWidget(m_btn_multichoice, 1, 2, 1, 1);

    QObject::connect(m_btn_no_token, &QPushButton::clicked, this, &GTokenMenu::selectTile);
    QObject::connect(m_btn_clear_tokens, &QPushButton::clicked, this, &GTokenMenu::clearTokens);

    if (m_caller->getNbNatureToken() > 0){
        QObject::connect(m_btn_multichoice, &QPushButton::clicked, this, &GTokenMenu::chooseMultiple);
    }

    // On connect a gdecktile
    QObject::connect(&GDeckTile::getInstance(), &GDeckTile::tileClicked, this, [this](int index) {
        m_spin_tile->setValue(index + 1); // ou autre
    });
    QObject::connect(&GDeckTile::getInstance(), &GDeckTile::tokenClicked, this, [this] (int index){
        m_spin_token->setValue(index +1);
    });

    //QObject::connect(m_decktile, &GDeckTile::tileClicked, this, &GTokenMenu::onTileClicked);

}

void GTokenMenu::onTileClicked(int index) {
    qDebug() << "Tuile cliquée dans le menu : " << index;

    // Tu veux probablement simuler ce que fait `pushResults` mais automatiquement :
    addResult(index);
    m_target->notifyInterface(3);

    // Optionnel : cacher le menu, désactiver decktile, etc.
    this->hide();
}

GTokenMenu::~GTokenMenu(){
    m_main_layout = nullptr;
    m_btn_validate = nullptr;
    m_btn_clear_tokens = nullptr;
    m_btn_no_token = nullptr;
    m_btn_multichoice = nullptr;
    m_label = nullptr;
    m_spin_tile = nullptr;
    m_spin_token = nullptr;
    m_spin_rota = nullptr;

}

void GTokenMenu::selectTile(){
    m_spin_tile = new QSpinBox(this);
    m_spin_tile->setMaximum(4);
    m_spin_tile->setMinimum(1);
    m_main_layout->addWidget(m_spin_tile, 2, 0, 1, 1);
    m_label_tile = new QLabel("Insérez ci dessous le numéro de la tuile", this);
    m_main_layout->addWidget(m_label_token, 1, 0, 1, 1);

    m_btn_clear_tokens->hide();
    m_btn_no_token->hide();
    m_btn_multichoice->hide();
    m_label->setText("Veuillez choisir le ou les éléménts par leur position");
    m_btn_validate = new QPushButton("Valider");
    m_main_layout->addWidget(m_btn_validate, 3, 0, 1, 1);

    m_btn_rotaD = new QPushButton("Droite");
    m_btn_rotaG = new QPushButton("Gauche");
    m_main_layout->addWidget(m_btn_rotaD,2,2,1,1);
    m_main_layout->addWidget(m_btn_rotaG,2,1,1,1);

    // Version spin box
    /*m_spin_rota = new QSpinBox(this);
    m_spin_rota->setMaximum(5);
    m_spin_tile->setMinimum(0);
    m_main_layout->addWidget(m_spin_rota,2,1,1,1);
    m_label_rota = new QLabel("Insérez ci dessous la rotation de la tuile", this);
    m_main_layout->addWidget(m_label_rota,1,1,1,1);*/

    QObject::connect(m_btn_rotaD, &QPushButton::clicked, this, [this]{rotate(true);});
    QObject::connect(m_btn_rotaG, &QPushButton::clicked, this, [this]{rotate(false);});
    QObject::connect(m_btn_validate, &QPushButton::clicked, this, &GTokenMenu::pushResults);
}

void GTokenMenu::clearTokens(){
    if (m_decktile->canFlushWithoutNaturetoken()){
        m_decktile->clearTokens();
        this->show();
        return;
    }
    m_decktile->clearTokens();
    m_caller->removeNatureToken();
    this->show();
    selectTile();
}

void GTokenMenu::chooseMultiple(){
    m_spin_token = new QSpinBox(this);
    m_spin_token->setMaximum(4);
    m_spin_token->setMinimum(1);
    m_main_layout->addWidget(m_spin_token, 2, 3, 1, 1);
    m_label_token = new QLabel("Insérez ci dessous le numéro du pion faune", this);
    m_main_layout->addWidget(m_label_token, 1, 3, 1, 1);
    m_caller->removeNatureToken();
    selectTile();
}

void GTokenMenu::pushResults(){
    addResult(m_spin_tile->value()-1);
    if (m_spin_token != nullptr){
        addResult(m_spin_token->value()-1);
    }
    m_target->notifyInterface(3);
}

void GTokenMenu::rotate(bool droite){
    if(!m_spin_tile)return;
    selected_tile = m_decktile->getTile(m_spin_tile->value()-1);
    selected_tile->Rotate(droite ? Anti_Trigonometric : Trigonometric);
    GDeckTile::getInstance().update(); // il faut utiliser l'instance et non gdecktile
}


void GTokenMenu::show(){
    m_decktile->show();
    return QWidget::show();
}

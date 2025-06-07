#include "gmessagebox.hpp"
#include <iostream>

GMessageBox::GMessageBox() : MessageBox(), QWidget(){
    m_main_layout = new QGridLayout(this);
}

GMessageBox::~GMessageBox(){
    std::cout << "DMB" << std::endl;

    for (size_t i = 0; i < m_labels.size(); i++){
        delete m_labels[i];
        m_labels[i] = nullptr;
    }
    this->hide();
    delete m_main_layout;
    m_main_layout = nullptr;
}


void GMessageBox::show(){
    for(const_iterator it = this->begin(); it != this->end(); ++it){
        m_labels.push_back(new QLabel(QString(it->getStr().c_str()), this));
        m_main_layout->addWidget(m_labels.back(), it->getRow(), it->getCol());
    }
    this->raise();
    this->activateWindow();
    QWidget::show();
}

void GMessageBox::closeEvent(QCloseEvent *event){
    reset();
    QWidget::closeEvent(event);
}

void GMessageBox::reset(){
    for (size_t i = 0; i < m_labels.size(); i++){
        delete m_labels[i];
        m_labels[i] = nullptr;
    }
    m_labels = {};
    MessageBox::reset();
}

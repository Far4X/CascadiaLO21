#ifndef GMESSAGEBOX_HPP
#define GMESSAGEBOX_HPP

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include <QCloseEvent>
#include "../../../Gametools/Abstract/messagebox.hpp"

class GMessageBox : public MessageBox, public QWidget{
    QGridLayout* m_main_layout;
    std::vector<QLabel*> m_labels;
public:
    GMessageBox();
    virtual ~GMessageBox();
    virtual void reset() override;
    virtual void show() override;
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // GMESSAGEBOX_HPP

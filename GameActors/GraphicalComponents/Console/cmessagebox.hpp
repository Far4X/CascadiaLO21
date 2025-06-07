#ifndef CMESSAGEBOX_HPP
#define CMESSAGEBOX_HPP

#include "../../../Gametools/Abstract/messagebox.hpp"

class CMessageBox : public MessageBox {
public:
    CMessageBox();
    virtual ~CMessageBox() = default;
    void show() override;
};

#endif // CMESSAGEBOX_HPP

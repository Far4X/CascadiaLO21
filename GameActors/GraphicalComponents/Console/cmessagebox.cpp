#include "cmessagebox.hpp"
#include <iostream>

CMessageBox::CMessageBox() : MessageBox(){

}

void CMessageBox::show(){
    unsigned int prev_row = this->begin()->getRow();
    unsigned int prev_col = this->begin()->getCol();
    std::cout << "----------------" << std::endl;
    for (const_iterator it = this->begin(); it != this->end(); ++it){
        std::cout << it->getStr() << " ";
        if (prev_row != it->getRow()){
            std::cout << std::endl;
        }
        else if (prev_col != it->getCol()){
            std::cout << " | ";
        }
    }
    std::cout << "----------------" << std::endl;
    reset();

}

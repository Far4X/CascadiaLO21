#include "messagebox.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

MessageBox::MessageBox() {}

void MessageBox::ordonateElems(){
    std::function<bool(stringElement &e1, stringElement &e2)> cmp = [](stringElement &e1, stringElement &e2){if (e1.getRow()<e2.getRow()){return true;}if (e1.getCol()<e2.getCol() && e1.getRow()==e2.getRow()){return true;} return false;};
    std::sort(m_elems.begin(), m_elems.end(), cmp);
}

void MessageBox::reset(){
    std::cout << "MBR" << std::endl;
    while(m_elems.size() > 0){
        m_elems.pop_back();
    }
}



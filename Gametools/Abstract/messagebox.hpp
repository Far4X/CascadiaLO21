#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP
#include "printable.hpp"

#include <string>
#include <vector>

class MessageBox : public Printable{
    class stringElement {
        std::string m_text = "";
        unsigned int m_row = 0;
        unsigned int m_col = 0;
    public :
        inline stringElement(const std::string& val, unsigned int row = 0, unsigned int col = 0) : m_text(val), m_row(row), m_col(col){};
        ~stringElement() = default;
        inline unsigned int getCol() const {return m_col;};
        inline unsigned int getRow() const {return m_row;};
        inline const std::string& getStr() const {return m_text;};
    };
    std::vector<stringElement> m_elems;
    void ordonateElems();

protected :
    class const_iterator{
        int m_current_id = 0;
        const MessageBox* m_box = nullptr;
    public :
        inline const_iterator(const MessageBox* box, unsigned int id) : m_current_id(id), m_box(box){};
        virtual ~const_iterator() = default;
        inline const stringElement& operator*(){return m_box->m_elems[m_current_id];};
        inline const_iterator& operator++(){m_current_id++; return *this;};
        inline bool operator!=(const const_iterator& other)const{return m_current_id != other.m_current_id;};
        inline const stringElement* operator->()const{return &(m_box->m_elems[m_current_id]);}
    };
    inline const_iterator begin()const{return const_iterator(this, 0);};
    inline const_iterator end()const{return const_iterator(this, m_elems.size());};

public:
    MessageBox();
    virtual ~MessageBox() = default;
    virtual void reset();
    void addMessage(std::string msg, unsigned int row = 0, unsigned int col = 0){m_elems.push_back(stringElement(msg, row, col));ordonateElems();};
};

#endif // MESSAGEBOX_HPP

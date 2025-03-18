#ifndef CUSTOMERROR_H
#define CUSTOMERROR_H
#include <string>
class CustomError {
    std::string m_msg;
    int m_id;
public:
    CustomError(std::string msg = "", int id = 1);
    int getCode() const;
    std::string getMessage() const;
};

#endif // CUSTOMERROR_H

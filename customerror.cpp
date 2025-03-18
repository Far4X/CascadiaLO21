#include "customerror.hpp"

CustomError::CustomError(std::string msg, int code) : m_msg(msg), m_id(code) {}

int CustomError::getCode() const {
    return m_id;
}

std::string CustomError::getMessage() const {
    return m_msg;
}

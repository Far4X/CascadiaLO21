#include "salvablething.hpp"

SalvableThing::SalvableThing() {}

std::vector<std::string> SalvableThing::separateParams(const std::string& raw, const char sep){
    std::vector<std::string> rt;
    std::string current_param;
    unsigned int bracket_level = 0;
    if (raw[0] != '{' || raw[raw.size()-1] != '}'){
        throw 99;
    }
    for (size_t i = 1; i < raw.size()-1; i++){
        if (raw[i] == sep && bracket_level == 0){
            rt.push_back(current_param);
            current_param = "";
        }
        else {
            current_param += raw[i];
            if (raw[i] == '{'){
                bracket_level++;
            }
            else if (raw[i] == '}'){
                bracket_level--;
            }
        }
    }
    return rt;
}

unsigned int SalvableThing::stringToInt(const std::string &raw){
    unsigned int rt = 0;
    for (size_t i = 0; i < raw.size(); i++){
        if (raw[i] >= '0' && raw[i] <= '9'){
            rt*=10;
            rt+= raw[i] - '0';
        }
        else {
            throw 99;
        }
    }
    return rt;
}


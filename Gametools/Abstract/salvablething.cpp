#include "salvablething.hpp"
#include <iostream>

SalvableThing::SalvableThing() {}

std::vector<std::string> SalvableThing::separateParams(const std::string& raw, const char sep){
    std::vector<std::string> rt;
    std::string current_param = "";
    unsigned int bracket_level = 0;
    /*if (raw[0] != '{' || raw[raw.size()-1] != '}'){
        std::cout << "Sep params got " << raw[0] << ", " << raw[1] << std::endl;
        throw 99;
    }*/
    for (size_t i = 0; i < raw.size(); i++){
        if (raw[i] == sep && bracket_level == 0){
            rt.push_back(current_param);
            current_param = "";
        }
        else {
            if (i != 0 || raw[i] != '{'){
                current_param += raw[i];

                if (raw[i] == '{'){
                    bracket_level++;
                }
                else if (raw[i] == '}'){
                    bracket_level--;
                }
            }
        }
    }
    if (sep != ';'){
        rt.push_back(current_param);
    }
    return rt;
}

unsigned int SalvableThing::stringToInt(const std::string &raw){
    unsigned int rt = 0;
    //std::cout << raw.size() << " : " << raw << std::endl;
    if ((raw.size() == 1 && !(raw[0] >= '0' && raw[0] <= '9'))|| raw.size() == 0){
        return 0;
    }
    for (size_t i = 0; i < raw.size(); i++){
        if (raw[i] >= '0' && raw[i] <= '9'){
            rt*=10;
            rt+= raw[i] - '0';
        }
        else if (i != raw.size()-1){
            std::cout << "Got :" << raw << "|" << std::endl;
            throw 99;
        }
    }
    return rt;
}


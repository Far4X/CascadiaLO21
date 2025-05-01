#include "playerboard.hpp"

PlayerBoard::PlayerBoard() : TileHolder(MAX_SIZE, MAX_SIZE){
    m_q_center = MAX_SIZE/2;
    m_r_center = MAX_SIZE/2;
}

std::string PlayerBoard::getSaveString() const {
    std::string desc = "c:";
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            if (getTile(i, j) != nullptr){
                desc += std::to_string(getTile(i, j)->getID()) + ";";
            }
        }
    }
    return desc;
}

void PlayerBoard::show(){

}


void PlayerBoard::moveHz(short int step){
    if ((step >= 0 && m_r_center > step) || (step < 0 && m_q_center >= 2*step)){ //TODO: check if superior to MAXSIZE;
        m_q_center += 2*step;
        m_r_center -= 1;
    }
}

void PlayerBoard::moveVt(short int step){
    if (step + m_q_center > 0 && step + m_q_center < MAX_SIZE){
        m_q_center += step;
    }
}

#include "playerboard.hpp"

PlayerBoard::PlayerBoard() : TileHolder(MAX_SIZE, MAX_SIZE){

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

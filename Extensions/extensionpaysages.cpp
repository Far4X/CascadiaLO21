#include "extensionpaysages.h"
#include <iostream>

void ExtensionPaysages::apply(Game& game) {
    std::cout << "[Extension] Chargement de l'extension Paysages...\n";
    game.setExtensionLoaded(true);
    game.extendMaxPlayers(6);

    game.loadExtensionTiles("Assets/Paysage/Tiles.lst");
    game.loadExtensionFauna("Assets/Paysage/Tokens.lst");
}

#ifndef EXTENSION_PAYSAGES_HPP
#define EXTENSION_PAYSAGES_HPP

#pragma once

#include "extension.h"
#include "GameActors/game.hpp"

class ExtensionPaysages : public IGameExtension {
public:
    void apply(Game& game) override;
};

#endif

#ifndef EXTENSION_HPP
#define EXTENSION_HPP

class Game;

class IGameExtension {
public:
    virtual ~IGameExtension() = default;
    virtual void apply(Game& game) = 0;
};

#endif

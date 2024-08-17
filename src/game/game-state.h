#pragma once

#include <memory>

class GameState {
  public:
    GameState() = default;
    GameState(const GameState &) = default;
    GameState(GameState &&) = delete;
    virtual GameState &operator=(const GameState &) = delete;
    virtual GameState &operator=(GameState &&) = delete;
    virtual ~GameState() = default;

    virtual std::unique_ptr<GameState> update() { return { nullptr }; }
    virtual void render() {}
};

#pragma once

class GameState {
  public:
    enum State {
        TITLE_SCREEN = 0,
        LOADING_SCREEN = 1,
        GAME = 2,
    };

    GameState() = default;
    GameState(const GameState &) = default;
    GameState(GameState &&) = delete;
    virtual GameState &operator=(const GameState &) = delete;
    virtual GameState &operator=(GameState &&) = delete;
    virtual ~GameState() = default;

    virtual State update() { return State {}; }
    virtual void render() {}
};

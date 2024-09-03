#pragma once

#include "network/peer-connection.h"
#include <memory>

class GameState {
  protected:
    std::shared_ptr<PeerConnection> m_peerConn;

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

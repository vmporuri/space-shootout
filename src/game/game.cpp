#include "game.h"
#include "game-state.h"
#include "game/game-message.h"
#include "laser.h"
#include "raylib.h"
#include "spaceship.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

// The basic Game constructor.
Game::Game() : m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 } {}

// Creates a Game object using a GameState object.
// This is typically used in the context of state transitions in the state
// machine.
Game::Game(const GameState &oldState)
    : GameState { oldState },
      m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 } {}

// Updates the Game's state by one tick.
std::unique_ptr<GameState> Game::update() {
    m_player.move();
    std::optional<Laser> blast { m_player.blast() };
    if (blast) {
        m_outgoingLasers.push_back(*blast);
    }
    return std::unique_ptr<GameState> {};
}

// Renders the Game screen.
void Game::render() {
    m_player.draw();
    for (auto &laser : m_outgoingLasers) {
        laser.move();
        laser.draw();
    }
}

// Sends the lasers that have gone off screen to the peer connection.
void Game::sendOutgoingLasers() {
    std::vector<int> exitingLasers {};
    m_outgoingLasers.erase(
        std::remove_if(m_outgoingLasers.begin(), m_outgoingLasers.end(),
                       [&exitingLasers](Laser laser) {
                           if (laser.isOffScreen()) {
                               exitingLasers.push_back(laser.getX());
                           }
                           return laser.isOffScreen();
                       }),
        m_outgoingLasers.end());
    GameMessage gameMsg { GameMessage::LASERS, exitingLasers };
    m_peerConn->sendPacket(gameMsg.marshall());
}

// Receives the incoming lasers from the peer connection and adds to the Game.
void Game::updateIncomingLasers() {
    PeerMessage msg { m_peerConn->checkForNewPackets() };
    if (msg.isDisconnection()) {
        return; // TODO: Implement automatic wins after opponent disconnection.
    }
    if (!msg.containsMessage()) {
        return;
    }

    GameMessage gameMsg { msg.getMessage() };
    switch (gameMsg.getMessageType()) {
    case GameMessage::LASERS: {
        std::vector<Laser> newLasers {};
        std::transform(gameMsg.getLasers().begin(), gameMsg.getLasers().end(),
                       std::back_inserter(newLasers), [](int posX) -> Laser {
                           return { posX, 0, Laser::DOWN };
                       });
        m_incomingLasers.insert(m_incomingLasers.end(), newLasers.begin(),
                                newLasers.end());
    }
    case GameMessage::DECLARE_LOSS:
        return;
    }
}

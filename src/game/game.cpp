#include "game.h"
#include "game-state.h"
#include "game/end-screen.h"
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
Game::Game()
    : m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 },
      m_isGameOver { false }, m_hasWon { false } {}

// Creates a Game object using a GameState object.
// This is typically used in the context of state transitions in the state
// machine.
Game::Game(const GameState &oldState)
    : GameState { oldState },
      m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 },
      m_isGameOver { false }, m_hasWon { false } {}

// Updates the Game's state by one tick.
std::unique_ptr<GameState> Game::update() {
    m_player.move();
    std::optional<Laser> blast { m_player.blast() };
    if (blast) {
        m_outgoingLasers.push_back(*blast);
    }
    std::for_each(m_outgoingLasers.begin(), m_outgoingLasers.end(),
                  [](Laser &laser) { laser.move(); });
    sendOutgoingLasers();
    updateIncomingLasers();
    std::for_each(m_incomingLasers.begin(), m_incomingLasers.end(),
                  [](Laser &laser) { laser.move(); });
    clearIncomingLasers();

    if (checkIfGameOver()) {
        auto nextState { std::make_unique<EndScreen>(*this) };
        nextState->setWinStatus(m_hasWon);
        return nextState;
    }
    return nullptr;
}

// Renders the Game screen.
void Game::render() {
    m_player.draw();
    std::for_each(m_outgoingLasers.begin(), m_outgoingLasers.end(),
                  [](Laser &laser) { laser.draw(); });
    std::for_each(m_incomingLasers.begin(), m_incomingLasers.end(),
                  [](Laser &laser) { laser.draw(); });
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
        m_isGameOver = true;
        m_hasWon = true;
        return;
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
    case GameMessage::DECLARE_LOSS: {
        m_isGameOver = true;
        m_hasWon = true;
        return;
    }
    }
}

// Clears incoming lasers that have gone off screen.
void Game::clearIncomingLasers() {
    m_incomingLasers.erase(
        std::remove_if(m_incomingLasers.begin(), m_incomingLasers.end(),
                       [](const Laser &laser) { return laser.isOffScreen(); }),
        m_incomingLasers.end());
}

// Returns true if the game is over and false otherwise.
bool Game::checkIfGameOver() const {
    return std::any_of(m_incomingLasers.begin(), m_incomingLasers.end(),
                       [this](const Laser &laser) {
                           return m_isGameOver || checkPlayerCollision(laser);
                       });
}

// Returns true if there is a collision between the player and the provided
// laser entity and false otherwise.
bool Game::checkPlayerCollision(const Laser &laser) const {
    if (CheckCollisionRecs(m_player.getRectangle(), laser.getRectangle())) {
        GameMessage gameMsg { GameMessage::DECLARE_LOSS, {} };
        m_peerConn->sendPacket(gameMsg.marshall());
        return true;
    }
    return false;
}

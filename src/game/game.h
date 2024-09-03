#pragma once

#include "game-state.h"
#include "laser.h"
#include "spaceship.h"
#include <memory>
#include <vector>

// The Game class controls the state and logic behind the core game.
// Manages the positions and movement of the player and all lasers.
// Communicates outgoing and incoming lasers with the peer connection.
// Dictates when the player has won/lost the game.
class Game : public GameState {
  private:
    Spaceship m_player;
    std::vector<Laser> m_outgoingLasers;
    std::vector<Laser> m_incomingLasers;

    // Sends the lasers that have gone off screen to the peer connection.
    void sendOutgoingLasers();

    // Receives the incoming lasers from the peer connection and adds them to
    // the Game.
    void updateIncomingLasers();

  public:
    // The basic Game constructor.
    Game();

    // Creates a Game object using a GameState object.
    // This is typically used in the context of state transitions in the state
    // machine.
    Game(const GameState &);

    // Updates the Game's state by one tick.
    std::unique_ptr<GameState> update() override;

    // Renders the Game screen.
    void render() override;
};

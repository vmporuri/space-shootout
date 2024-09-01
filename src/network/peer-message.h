#pragma once

#include <string>

enum MessageType { NO_MESSAGE = 0, MESSAGE = 1, DISCONNECTION = 2 };

class PeerMessage {
  private:
    MessageType m_type;
    std::string m_msg;

  public:
    PeerMessage(MessageType type);
    PeerMessage(std::string &msg);
    [[nodiscard]] bool containsMessage() const;
    [[nodiscard]] bool isDisconnection() const;
    [[nodiscard]] const std::string &getMessage() const;
};

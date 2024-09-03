#pragma once

#include <string>
#include <vector>

class GameMessage {

  public:
    enum MessageType { LASERS = 0, DECLARE_LOSS = 1 };

  private:
    constexpr static auto s_messageField { "messageType" };
    constexpr static auto s_incomingField { "incomingLasers" };

    MessageType m_type;
    std::vector<int> m_lasers;

  public:
    GameMessage(MessageType type, const std::vector<int> &lasers);
    GameMessage(const std::string &msg);
    [[nodiscard]] MessageType getMessageType() const;
    [[nodiscard]] std::vector<int> getLasers() const;
    [[nodiscard]] std::string marshall() const;
    void unmarshall(std::string msg);
};

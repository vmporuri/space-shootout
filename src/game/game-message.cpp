#include "game-message.h"
#include "nlohmann/json.hpp"

GameMessage::GameMessage(MessageType type, const std::vector<int> &lasers)
    : m_type { type }, m_lasers { lasers } {}

GameMessage::GameMessage(const std::string &msg) : m_type {} {
    unmarshall(msg);
}

[[nodiscard]] GameMessage::MessageType GameMessage::getMessageType() const {
    return m_type;
}

[[nodiscard]] std::vector<int> GameMessage::getLasers() const {
    return m_lasers;
}

[[nodiscard]] std::string GameMessage::marshall() const {
    nlohmann::json msgJSON;
    msgJSON[s_messageField] = (int)m_type;
    msgJSON[s_incomingField] = m_lasers;
    return msgJSON.dump();
}

void GameMessage::unmarshall(std::string msg) {
    nlohmann::json msgJSON { nlohmann::json::parse(msg) };

    if (msgJSON.contains(s_messageField) &&
        msgJSON[s_messageField].is_number_integer()) {
        m_type = msgJSON[s_messageField];
    }

    if (msgJSON.contains(s_incomingField) &&
        msgJSON[s_incomingField].is_array()) {
        m_lasers = msgJSON[s_incomingField].get<std::vector<int>>();
    }
}

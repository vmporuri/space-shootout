#include "network/peer-message.h"
#include <string>

PeerMessage::PeerMessage(MessageType type) : m_type { type } {}

PeerMessage::PeerMessage(std::string &msg)
    : m_type { MESSAGE }, m_msg { std::move(msg) } {}

[[nodiscard]] bool PeerMessage::containsMessage() const {
    return m_type == MESSAGE;
}

[[nodiscard]] bool PeerMessage::isDisconnection() const {
    return m_type == DISCONNECTION;
}

[[nodiscard]] const std::string &PeerMessage::getMessage() const {
    return m_msg;
}

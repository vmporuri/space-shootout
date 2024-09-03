#include "host-connection.h"
#include "enet/enet.h"
#include "network/enet-deleters.h"
#include "network/peer-message.h"
#include <memory>
#include <string>

HostConnection::HostConnection() {
    ENetAddress sourceAddr;
    sourceAddr.host = ENET_HOST_ANY;
    sourceAddr.port = s_defaultPort;
    m_server = std::unique_ptr<ENetHost, ENetHostDeleter>(enet_host_create(
        &sourceAddr, s_numPeers, s_numPeers, s_bandwidth, s_bandwidth));
    if (!m_server) {
        std::cerr << "Error initializing ENet server.\n";
        std::exit(EXIT_FAILURE);
    }
}

// Returns true if a peer connects within the connection timeout limit.
bool HostConnection::findPeer() {
    ENetEvent event;
    while (enet_host_service(m_server.get(), &event, 0) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            return true;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;
        default:
            break;
        }
    }
    return false;
}

// Sends a packet containing msg to the client connection.
void HostConnection::sendPacket(std::string msg) {
    std::unique_ptr<ENetPacket, ENetPacketNonDeleter> packet {
        enet_packet_create(msg.c_str(), msg.length() + 1, 0)
    };
    enet_host_broadcast(m_server.get(), 0, packet.get());
    enet_host_flush(m_server.get());
}

// Checks for new packets from the client connection.
// Returns result in a PeerMessage object.
PeerMessage HostConnection::checkForNewPackets() {
    ENetEvent event;
    while (enet_host_service(m_server.get(), &event, 0) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_RECEIVE: {
            std::string msg { reinterpret_cast<const char *>(
                event.packet->data) };
            PeerMessage peerMsg { msg };
            enet_packet_destroy(event.packet);
            return peerMsg;
        }
        case ENET_EVENT_TYPE_DISCONNECT:
            return { DISCONNECTION };
        default:
            break;
        }
    }
    return { NO_MESSAGE };
}

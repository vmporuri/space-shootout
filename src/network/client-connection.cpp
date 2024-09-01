#include "enet/enet.h"
#include "network/enet-deleters.h"
#include "network/peer-connection.h"
#include "network/peer-message.h"

class ClientConnection : public PeerConnection {
  private:
    std::unique_ptr<ENetPeer, ENetPeerDeleter> m_peer;
    std::unique_ptr<ENetHost, ENetHostDeleter> m_client;

  public:
    ClientConnection()
        : m_client { enet_host_create(nullptr, s_numPeers, s_numPeers,
                                      s_bandwidth, s_bandwidth) } {}

    // Returns true if able to connect to a peer within the connection timeout
    // limit.
    bool findPeer() override {
        ENetAddress peerAddr;
        peerAddr.host = ENET_HOST_BROADCAST;
        peerAddr.port = s_defaultPort;
        m_peer = std::unique_ptr<ENetPeer, ENetPeerDeleter>(enet_host_connect(
            m_client.get(), &peerAddr, s_numPeers, s_bandwidth));

        ENetEvent event;
        while (enet_host_service(m_client.get(), &event,
                                 s_connectionTimeoutLength) > 0) {
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

    // Attempts to gently disconnect from the host.
    // If cannot do so prior to the timeout limit, forcibly disconnects.
    void disconnectPeer() override {
        enet_peer_disconnect(m_peer.get(), 0);

        ENetEvent event;
        while (enet_host_service(m_client.get(), &event,
                                 s_connectionTimeoutLength) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                return;
            default:
                break;
            }
        }
        m_peer.reset();
    };

    // Sends a packet containing msg to the host connection.
    void sendPacket(std::string msg) override {
        std::unique_ptr<ENetPacket, ENetPacketNonDeleter> packet {
            enet_packet_create(msg.c_str(), msg.length() + 1, 0)
        };
        enet_peer_send(m_peer.get(), 0, packet.get());
        enet_host_flush(m_client.get());
    }

    // Checks for new packets from the client connection.
    // Returns result in a PeerMessage object.
    PeerMessage checkForNewPackets() override {
        ENetEvent event;
        while (enet_host_service(m_client.get(), &event, 0) > 0) {
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
};

#include "enet/enet.h"
#include "network/enet-deleters.h"
#include "network/peer-connection.h"
#include <memory>

class HostConnection : public PeerConnection {
  private:
    std::unique_ptr<ENetHost, ENetHostDeleter> m_server;

  public:
    HostConnection() {
        ENetAddress sourceAddr;
        sourceAddr.host = ENET_HOST_ANY;
        sourceAddr.port = s_defaultPort;
        m_server = std::unique_ptr<ENetHost, ENetHostDeleter>(enet_host_create(
            &sourceAddr, s_numPeers, s_numPeers, s_bandwidth, s_bandwidth));
    }

    // Returns true if a peer connects within the connection timeout limit.
    bool findPeer() override {
        ENetEvent event;
        while (enet_host_service(m_server.get(), &event,
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

    // Relies on the client connection to disconnect.
    void disconnectPeer() override {}
};

#include "enet.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

class PeerConnection {
  private:
    static inline bool s_isENetInitialized { false };
    static constexpr int s_defaultServerPort { 1234 };
    static constexpr int s_defaultScannerPort { 5678 };

    // TODO: Create custom C++ wrappers for ENet classes
    std::unique_ptr<ENetHost> m_server;
    std::unique_ptr<ENetHost> m_client;
    std::unique_ptr<ENetSocket> m_scanner;
    std::unique_ptr<ENetAddress> m_address;

  public:
    PeerConnection() : m_address { std::make_unique<ENetAddress>() } {
        initENet();

        m_address->host = ENET_HOST_ANY;
        m_address->port = s_defaultServerPort;
        m_server = std::unique_ptr<ENetHost>(
            enet_host_create(m_address.get(), 2, 2, 0, 0));
        if (m_server == nullptr) {
            std::cerr << "Error setting up game server.\n";
            return;
        }

        m_client =
            std::unique_ptr<ENetHost>(enet_host_create(nullptr, 1, 1, 0, 0));
        if (m_client == nullptr) {
            std::cerr << "Error setting up networking client.\n";
            return;
        }

        m_scanner = std::make_unique<ENetSocket>(
            enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM));
        if (*m_scanner == ENET_SOCKET_NULL) {
            std::cerr << "Error creating LAN scanner.\n";
            return;
        }
        enet_socket_set_option(*m_scanner, ENET_SOCKOPT_BROADCAST, 1);
    }

    static void initENet() {
        if (!s_isENetInitialized) {
            if (enet_initialize() != 0) {
                std::cerr << "Error initializing ENet library.\n";
                std::exit(EXIT_FAILURE);
            }
            std::atexit(enet_deinitialize);
            s_isENetInitialized = true;
        }
    }

    void searchForPeers() {
        ENetAddress scanAddress;
        // FIXME: Add broadcast IP for IPv6.
        // scanAddress.host = ENET_HOST_BROADCAST;
        scanAddress.port = s_defaultScannerPort;
    }

    void sendPacket() {}

    std::string checkForNewPackets() {
        ENetEvent event;
        if (enet_host_service(m_server.get(), &event, 0) <= 0) {
            std::cerr << "Error servicing host.\n";
            return {};
        }

        switch (event.type) {
        case ENET_EVENT_TYPE_NONE:
            return {};
        case ENET_EVENT_TYPE_CONNECT:
            return {};
        case ENET_EVENT_TYPE_RECEIVE:
            return { reinterpret_cast<char *>(event.packet->data),
                     event.packet->dataLength };
        case ENET_EVENT_TYPE_DISCONNECT:
        case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
            return {};
        }

        enet_packet_destroy(event.packet);
        event.peer->data = nullptr;
    }
};

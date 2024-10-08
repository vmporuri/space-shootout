#pragma once

#include "enet/enet.h"
#include "network/peer-message.h"
#include <cstdlib>
#include <iostream>

class PeerConnection {
  protected:
    static inline bool s_isENetInitialized { false };
    static constexpr int s_defaultPort { 7778 };
    static constexpr int s_numPeers { 1 };
    static constexpr int s_bandwidth { 0 };
    static constexpr int s_connectionTimeoutLength { 5000 };

  public:
    PeerConnection() = default;
    PeerConnection(const PeerConnection &) = default;
    PeerConnection(PeerConnection &&) = delete;
    PeerConnection &operator=(const PeerConnection &) = default;
    PeerConnection &operator=(PeerConnection &&) = delete;
    virtual ~PeerConnection() = default;

    virtual bool findPeer() { return true; }
    virtual void sendPacket([[maybe_unused]] std::string msg) {}
    virtual PeerMessage checkForNewPackets() { return { NO_MESSAGE }; }
    virtual void disconnectPeer() {}

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
};

#pragma once

#include "enet/enet.h"
#include "network/enet-deleters.h"
#include "network/peer-connection.h"
#include "network/peer-message.h"
#include <memory>
#include <string>

class HostConnection : public PeerConnection {
  private:
    std::unique_ptr<ENetHost, ENetHostDeleter> m_server;

  public:
    HostConnection();

    // Returns true if a peer connects within the connection timeout limit.
    bool findPeer() override;

    // Relies on the client connection to disconnect.
    void disconnectPeer() override {}

    // Sends a packet containing msg to the client connection.
    void sendPacket(std::string msg) override;

    // Checks for new packets from the client connection.
    // Returns result in a PeerMessage object.
    PeerMessage checkForNewPackets() override;
};

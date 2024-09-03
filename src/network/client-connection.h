#pragma once

#include "enet/enet.h"
#include "network/enet-deleters.h"
#include "network/peer-connection.h"
#include "network/peer-message.h"

class ClientConnection : public PeerConnection {
  private:
    std::unique_ptr<ENetPeer, ENetPeerDeleter> m_peer;
    std::unique_ptr<ENetHost, ENetHostDeleter> m_client;

  public:
    ClientConnection();

    // Returns true if able to connect to a peer within the connection timeout
    // limit.
    bool findPeer() override;

    // Attempts to gently disconnect from the host.
    // If cannot do so prior to the timeout limit, forcibly disconnects.
    void disconnectPeer() override;

    // Sends a packet containing msg to the host connection.
    void sendPacket(std::string msg) override;

    // Checks for new packets from the client connection.
    // Returns result in a PeerMessage object.
    PeerMessage checkForNewPackets() override;
};

#pragma once

#include "enet/enet.h"

class ENetHostDeleter {
  public:
    void operator()(ENetHost *hostPtr) const { enet_host_destroy(hostPtr); }
};

class ENetPeerDeleter {
  public:
    void operator()(ENetPeer *peerPtr) const { enet_peer_reset(peerPtr); }
};

class ENetPacketDeleter {
  public:
    void operator()(ENetPacket *packetPtr) const {
        enet_packet_destroy(packetPtr);
    }
};

class ENetPacketNonDeleter {
  public:
    void operator()(ENetPacket *packetPtr) const {}
};

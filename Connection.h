//
// Created by matej on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_CONNECTION_H
#define PONG_SEMESTRALKA_CONNECTION_H

#include <thread>
#include "SFML/Network.hpp"
#include <SFML/System.hpp>
#include "GamePlayer.h"
using namespace std;
using namespace sf;

class Connection {
private:
    UdpSocket socket;
    IpAddress ipAddress;
    unsigned short port;
    bool isServer;
public:
    Connection(unsigned short  port);

    ~Connection();
    void connect(IpAddress ipAddress);
    void recievePacketPlayerInfo(GamePlayer* player, double posX);

    void sendPacketPlayerInfo(double position);

    void sendConnectEstablish(string message);
    void recieveEstablish(string& message);

    const IpAddress &getIpAddress() const;

    const UdpSocket &getSocket() const;

    void setIpAddress(const IpAddress &ipAddress);
};


#endif //PONG_SEMESTRALKA_CONNECTION_H

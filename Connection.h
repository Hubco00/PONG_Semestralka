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
    TcpSocket socket;
    IpAddress ipAddress;
    unsigned short port;
    bool isServer;
public:
    Connection(unsigned short  port);

    ~Connection();
    bool connect(IpAddress ipAddress);
    void disconnect();
    void recievePacketPlayerInfo(GamePlayer* player, double posX);

    void sendPacketPlayerInfo(double position);

    bool sendConnectEstablish(string message);
    bool recieveEstablish(string& message);

    const IpAddress &getIpAddress() const;

    TcpSocket &getSocket();

    void setIpAddress(const IpAddress &ipAddress);

};


#endif //PONG_SEMESTRALKA_CONNECTION_H

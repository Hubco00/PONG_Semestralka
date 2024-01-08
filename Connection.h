//
// Created by matej on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_CONNECTION_H
#define PONG_SEMESTRALKA_CONNECTION_H

#include <thread>
#include "SFML/Network.hpp"
#include <SFML/System.hpp>
#include "GamePlayer.h"
#include "Ball.h"
#include "PacketTypes.h"
#include <mutex>
using namespace std;
using namespace sf;
using namespace Pong;

class Connection {
private:
    TcpSocket socket;
    IpAddress ipAddress;
    unsigned short port;
    bool isServer;
    bool connected;
public:
    Connection(unsigned short  port);

    ~Connection();
    bool connect(IpAddress ipAddress);
    void disconnect();
    void recievePacketPlayerInfo(GamePlayer* player, double posX);

    void sendPacketPlayerInfo(PacketTypes packetTypes, double position);

    void sendPacketBallInfo(PacketTypes packetTypes,float x, float y);
    Vector2f recievePacketBallInfo();

    void sendPacketScoreInfo(int score);
    int recievePacketScoreInfo();

    bool sendConnectEstablish(string message);
    bool recieveEstablish(string& message);

    bool getConnected();

    void setConnected(bool condition);


    const IpAddress &getIpAddress() const;

    TcpSocket &getSocket();

    void listen(GamePlayer* player, Ball* ball, mutex* mutex);

    void setIpAddress(const IpAddress &ipAddress);

    void extractFromPackets(Packet packet, GamePlayer* player, Ball* ball);
};


#endif //PONG_SEMESTRALKA_CONNECTION_H

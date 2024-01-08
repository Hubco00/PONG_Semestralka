//
// Created by matej on 4. 1. 2024.
//

#include "Connection.h"

Connection::Connection(unsigned short port) : port(port)
{
    this->connected = false;
}

Connection::~Connection() {

}

bool Connection::connect(IpAddress ipAddress) {
    if (socket.connect(ipAddress, port) != Socket::Done) {
        cerr << "Failed to connect." << endl;
        return false;
    }
    return true;
}

void Connection::disconnect() {
    socket.disconnect();
}



void Connection::recievePacketPlayerInfo(GamePlayer* player, double posX) {
    Packet packet;
    this->socket.receive(packet);
    double posY;
    packet >> posY;
    player->setPlayerPosition(posX, posY);
}

void Connection::sendPacketPlayerInfo(PacketTypes packetTypes, double position) {
    Packet packet;
    packet << (int)packetTypes << position << 0;
    this->socket.send(packet);
}

const IpAddress &Connection::getIpAddress() const {
    return ipAddress;
}

void Connection::setIpAddress(const IpAddress &ipAddress) {
    Connection::ipAddress = ipAddress;
}

TcpSocket &Connection::getSocket() {
    return socket;
}


void Connection::sendPacketBallInfo(PacketTypes packetTypes,float x, float y) {
    Packet packet;
    packet << (int)packetTypes << x << y;
    this->socket.send(packet);
}

Vector2f Connection::recievePacketBallInfo() {
    Packet packet;
    this->socket.receive(packet);
    float posY;
    float posX;
    packet >> posX >> posY;
    Vector2f positions = {posX, posY};
    return positions;
}

void Connection::sendPacketScoreInfo(int score) {
    Packet packet;
    packet << score;
    this->socket.send(packet);
}

int Connection::recievePacketScoreInfo() {
    Packet packet;
    this->socket.receive(packet);
    int score;
    packet >> score;
    return score;
}

bool Connection::isConnected() const {
    return connected;
}

void Connection::setConnected(bool condition) {
    Connection::connected = condition;
}

void Connection::listen(GamePlayer* player, Ball* ball) {
    Packet packet;
    while(this->connected)
    {
        if(this->socket.receive(packet) == Socket::Done)
        {
            extractFromPackets(packet, player, ball);
        }
    }
}

void Connection::extractFromPackets(Packet packet, GamePlayer* player, Ball* ball)
{
    int packetType;
    float firstPacketInfo, secondPacketInfo;
    packet >> packetType >> firstPacketInfo >> secondPacketInfo;
    switch (packetType) {
        case 3:
            player->setCurrentPositions((double)firstPacketInfo, (double)secondPacketInfo);
            break;
        case 4:
            ball->redrawToPos((double)firstPacketInfo, (double)secondPacketInfo);
            break;
    }

}

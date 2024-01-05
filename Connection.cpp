//
// Created by matej on 4. 1. 2024.
//

#include "Connection.h"

Connection::Connection(unsigned short port) : port(port)
{
    this->socket.bind(port);
}

Connection::~Connection() {

}

void Connection::connect(IpAddress ipAddress) {
    this->ipAddress = ipAddress;
    this->socket.bind(port);
}


void Connection::recievePacketPlayerInfo(GamePlayer* player, double posX) {
    Packet packet;
    this->socket.receive(packet, this->ipAddress, this->port);
    double posY;
    packet >> posY;
    player->setPlayerPosition(posX, posY);
}

void Connection::sendPacketPlayerInfo(double position) {
    Packet packet;
    packet << position;
    this->socket.send(packet, this->ipAddress, this->port);
}

const IpAddress &Connection::getIpAddress() const {
    return ipAddress;
}

void Connection::setIpAddress(const IpAddress &ipAddress) {
    Connection::ipAddress = ipAddress;
}

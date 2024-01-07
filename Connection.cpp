//
// Created by matej on 4. 1. 2024.
//

#include "Connection.h"

Connection::Connection(unsigned short port) : port(port)
{

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

void Connection::sendPacketPlayerInfo(double position) {
    Packet packet;
    packet << position;
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

bool Connection::sendConnectEstablish(string message) {
    Packet packet;
    packet << message;
    if(this->socket.send(packet) != Socket::Done)
    {
        cerr << "Failed to send messahe." << endl;
        return false;
    }
    return true;
}

bool Connection::recieveEstablish(string& message) {
    Packet packet;
    if(this->socket.receive(packet) != Socket::Done)
    {
        std::cerr << "Failed to receive message" << std::endl;
        return false;
    }
    packet >> message;
    return true;
}

void Connection::sendPacketBallInfo(double x, double y) {
    Packet packet;
    packet << x << y;
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

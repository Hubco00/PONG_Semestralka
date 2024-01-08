//
// Created by adria on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_GAME_H
#define PONG_SEMESTRALKA_GAME_H
#include <SFML/Network.hpp>
#include "Ball.h"
#include "GamePlayer.h"
#include "PacketTypes.h"
#include <SFML/System.hpp>
#include "thread"
#include "mutex"
#include "queue"
#include <condition_variable>
#include <chrono>
#define PORT 50145
using namespace std;
using namespace Pong;
class Game {
private:
    int height = 500;
    int width = 750;
    Ball* ball;
    GamePlayer* player1;
    GamePlayer* player2;
    Font font;
    Text scorePlayer1;
    Text scorePlayer2;
    Text winnedGames1;
    Text winnedGames2;
    PacketTypes packetTypes;
    TcpListener listener;
    TcpSocket socket;
    IpAddress ipAddress;
    bool listening = false;
    std::thread listeningThread;


public:
    Game();
    ~Game();
    void drawAll(RenderWindow *window);
    void setFont(RenderWindow* window);
    void drawNew(RenderWindow* window, double x, double y);
    void Play(RenderWindow* window);
    void keyInput(RenderWindow* window);
    void connect();
    void listen();
    void send(PacketTypes packetTypes, float firstInfo, float secondInfo);
    void extractFromPackets(Packet packet, GamePlayer* player, Ball* ball);
    void setNewWinner(GamePlayer* player, RenderWindow* window);
    void checkIfWinner(RenderWindow* window);
};




#endif //PONG_SEMESTRALKA_GAME_H

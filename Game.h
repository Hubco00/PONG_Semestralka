//
// Created by adria on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_GAME_H
#define PONG_SEMESTRALKA_GAME_H
#include <SFML/Network.hpp>
#include "Ball.h"
#include "GamePlayer.h"
#include "PacketTypes.h"
#include "Connection.h"
#include <SFML/System.hpp>
#include "thread"
#include "mutex"

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
    Text scorePlayer1;
    Text scorePlayer2;
    Font font;
    bool end;
    PacketTypes packetTypes;
    thread thread;
    Connection* con;
public:
    Game();
    ~Game();
    void drawAll(RenderWindow *window);
    void setFont(RenderWindow* window);
    void drawNew(RenderWindow* window, double x, double y);
    void drawNewScore(RenderWindow* window);
    void Play(RenderWindow* window);
    void keyInput(Keyboard::Key key);
    void connect();

};




#endif //PONG_SEMESTRALKA_GAME_H

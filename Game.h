//
// Created by adria on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_GAME_H
#define PONG_SEMESTRALKA_GAME_H
#include "Ball.h"
#include "GamePlayer.h"


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
public:
    Game();
    ~Game();
    void drawAll(RenderWindow *window);
    void setFont(RenderWindow* window);
    void keyInput(Keyboard::Key key);


};




#endif //PONG_SEMESTRALKA_GAME_H

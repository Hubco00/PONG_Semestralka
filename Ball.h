//
// Created by adria on 4. 1. 2024.
//
#include <SFML/Graphics.hpp>
#include "GamePlayer.h"
#ifndef PONG_SEMESTRALKA_BALL_H
#define PONG_SEMESTRALKA_BALL_H
using namespace std;
using namespace sf;
namespace Pong {
    class Ball {
    private:;
        CircleShape ball;
        double movementX = 2;
        double movementY = 0;
        double posX;
        double posY;
    public:
        Ball(double startPosX, double startPosY);
        Vector2f getPosition();
        CircleShape getBall();
        void setPositions(double x, double y);
        void move();
        void draw(RenderWindow * window,double positionX, double positionY);
        void redrawToPos(double x, double y);
        FloatRect getBoundsOfBall();
        double getMovementX() const;
        void setMovementXMinus();
        void setMovementXPlus();
        double getMovementY() const;
        void setMovementYMinus();
        void setMovementYPLus();
        double getPosX() const;
        void setPosX(double startPosX);
        double getPosY() const;
        void setPosY(double startPosY);
        void updateMovementOfBall(GamePlayer* player1, GamePlayer* player2, RenderWindow* window);
    };
}


#endif //PONG_SEMESTRALKA_BALL_H

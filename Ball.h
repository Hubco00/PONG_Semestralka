//
// Created by adria on 4. 1. 2024.
//
#include <SFML/Graphics.hpp>
#include <string>
#ifndef PONG_SEMESTRALKA_BALL_H
#define PONG_SEMESTRALKA_BALL_H
using namespace std;
using namespace sf;
class Ball {
private:
    int width;
    int height;
    CircleShape ball;
public:
    Ball(double positionX, double positionY);

};


#endif //PONG_SEMESTRALKA_BALL_H

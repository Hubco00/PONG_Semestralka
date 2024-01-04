//
// Created by adria on 4. 1. 2024.
//

#include "Ball.h"

Pong::Ball::Ball(double startPosX, double startPosY) {
    this->startPosX = startPosX;
    this->startPosY = startPosY;
}

Vector2f Pong::Ball::getPosition() {
    return this->ball.getPosition();
}

CircleShape Pong::Ball::getBall() {
    return this->ball;
}

void Pong::Ball::setPositions(double x, double y) {
    this->ball.setPosition(x,y);
}

void Pong::Ball::move() {
    this->ball.move(this->movementX,this->movementY);
}


void Pong::Ball::draw(RenderWindow *window, double positionX, double positionY) {
    this->ball.setFillColor(Color::White);
    this->ball.setRadius(5);
    this->setPositions(positionX,positionY);
    window->draw(this->ball);
}

void Pong::Ball::redrawToStartPos(double x, double y, int winner) {
    this->setStartPosX(x);
    this->setStartPosY(y);
}


double Pong::Ball::getMovementX() const {
    return this->movementX;
}

void Pong::Ball::setMovementXMinus(double movementX) {
    this->movementX = -movementX;
}

void Pong::Ball::setMovementXPlus(double movementX) {
    this->movementX = +movementX;
}

double Pong::Ball::getMovementY() const {
    return this->movementY;
}

void Pong::Ball::setMovementYMinus(double movementY) {
    this->movementY = -movementY;
}

void Pong::Ball::setMovementYPLus(double movementY) {
    this->movementY = +movementY;
}

double Pong::Ball::getStartPosX() const {
    return this->startPosX;
}

void Pong::Ball::setStartPosX(double startPosX) {
    this->startPosX = startPosX;
}

double Pong::Ball::getStartPosY() const {
    return this->startPosY;
}

void Pong::Ball::setStartPosY(double startPosY) {
    this->startPosY = startPosY;
}





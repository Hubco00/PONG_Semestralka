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

void Pong::Ball::setMovementXMinus() {
    this->movementX = -this->movementX;
}

void Pong::Ball::setMovementXPlus() {
    this->movementX = +this->movementX;
}

double Pong::Ball::getMovementY() const {
    return this->movementY;
}

void Pong::Ball::setMovementYMinus() {
    this->movementY = -this->movementY;
}

void Pong::Ball::setMovementYPLus() {
    this->movementY = +this->movementY;
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

void Pong::Ball::updateMovementOfBall(GamePlayer* player1, GamePlayer* player2, RenderWindow* window) {
    // Move the ball
    this->ball.move(this->movementX, this->movementY);

    // Get ball position and bounds
    Vector2f ballPosition = this->ball.getPosition();
    FloatRect ballBounds = this->ball.getGlobalBounds();

    // Check for collision with top and bottom of the screen
    if (ballPosition.y <= 0 || ballPosition.y >= window->getSize().y - ballBounds.height) {
        this->movementY = -this->movementY; // Reverse Y movement
    }

    // Get player bounds
    FloatRect player1Bounds = player1->getGlobalBoundsOfPlayer();
    FloatRect player2Bounds = player2->getGlobalBoundsOfPlayer();

    // Check for collision with player 1 and player 2 paddles
    if (ballBounds.intersects(player1Bounds) || ballBounds.intersects(player2Bounds)) {
        this->movementX = -this->movementX; // Reverse X movement

        // Adjust Y movement based on where it hit the paddle
        float paddleCenterY;
        if (ballBounds.intersects(player1Bounds)) {
            paddleCenterY = player1Bounds.top + player1Bounds.height / 2;
        } else {
            paddleCenterY = player2Bounds.top + player2Bounds.height / 2;
        }

        float impactPoint = (ballPosition.y + ballBounds.height / 2) - paddleCenterY;
        float normalizedImpact = impactPoint / (player1Bounds.height / 2); // Normalize the impact to a range of -1 to 1
        const float MAX_ANGLE = 5.0f; // Max angle change
        this->movementY += normalizedImpact * MAX_ANGLE;
    }
}


FloatRect Pong::Ball::getBoundsOfBall() {
    return this->ball.getGlobalBounds();
}






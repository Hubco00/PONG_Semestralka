//
// Created by matej on 4. 1. 2024.
//

#include "GamePlayer.h"

// Konstruktor kde musime inicializovat startovacei pozicie
GamePlayer::GamePlayer(float startX, float startY)
{
    this->currentPositionX = startX;
    this->initialPositionX = startX;
    this->currentPositionY = startY;
    this->initialPositionY = startY;
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::ascend()
{
    this->currentPositionY -= 5;
}

void GamePlayer::descend()
{
    this->currentPositionY += 5;
}

void GamePlayer::render(RenderWindow* window)
{
    this->player.setSize(Vector2f(8, 45));
    player.setPosition(currentPositionX,currentPositionY);
    player.setFillColor(Color::Yellow);
    window->draw(player);
}

void GamePlayer::move(float deltaX, float deltaY)
{
    this->currentPositionX += deltaX;
    this->currentPositionY += deltaY;
}

void GamePlayer::setCurrentPositions(double currentPositionX, double currentPositionY) {
    this->currentPositionX = currentPositionX;
    this->currentPositionY = currentPositionY;
}


void GamePlayer::resetPosition()
{
    this->currentPositionX = initialPositionX;
    this->currentPositionY = initialPositionY;

}

FloatRect GamePlayer::getGlobalBoundsOfPlayer() {
    return player.getGlobalBounds();
}

void GamePlayer::plusScore() {
    this->playerScore++;
}

void GamePlayer::resetScore() {
    this->playerScore = 0;
}

void GamePlayer::setPlayerPosition(double posX, double posY ) {
    this->player.setPosition(posX, posY);
}



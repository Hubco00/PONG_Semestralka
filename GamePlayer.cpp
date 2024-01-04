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
    player.setPosition(initialPositionX,initialPositionY);
    player.setFillColor(Color::Yellow);
    window->draw(player);
}

void GamePlayer::move(float deltaX, float deltaY)
{
    this->currentPositionX += deltaX;
    this->currentPositionY += deltaY;
}

void GamePlayer::resetPosition()
{
    this->currentPositionX = initialPositionX;
    this->currentPositionY = initialPositionY;

}

FloatRect GamePlayer::getGlobalBoundsOfPlayer() const {
    return player.getGlobalBounds();
}

void GamePlayer::plusScore() {
    this->playerScore++;
}



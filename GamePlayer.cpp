//
// Created by matej on 4. 1. 2024.
//

#include "GamePlayer.h"

// Konstruktor kde musime inicializovat startovacei pozicie
GamePlayer::GamePlayer(float startX, float startY)
{
    this->currentPosition = Vector2f (startX,startY);
    this->initialPosition = Vector2f (startX,startY);
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::ascend()
{
    this->currentPosition.y -= 5;
}

void GamePlayer::descend()
{
    this->currentPosition.y += 5;
}

void GamePlayer::render(RenderWindow* window)
{
    RectangleShape player(Vector2f(8, 45));
    player.setPosition(initialPosition);
    player.setFillColor(Color::Yellow);
    window->draw(player);
}

void GamePlayer::move(float deltaX, float deltaY)
{
    this->currentPosition.x += deltaX;
    this->currentPosition.y += deltaY;
}

void GamePlayer::resetPosition()
{
    this->currentPosition = initialPosition;
}


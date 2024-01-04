//
// Created by adria on 4. 1. 2024.
//
#include <string>
#include "Game.h"

using namespace std;

void Game::drawAll(RenderWindow *window) {
    this->ball = new Ball((this->width / 2), (this->height/2));
    this->player1 = new GamePlayer(0, (this->height / 2) - 22);
    this->player2 = new GamePlayer(width - 8, (this->height / 2) - 22);
    window->create(VideoMode(this->width, this->height), "Pong");
    window->setFramerateLimit(60);
    this->player1->render(window);
    this->player2->render(window);
    this->ball->draw(window, this->ball->getStartPosX(), this->ball->getStartPosY());
}

void Game::setFont(RenderWindow *window) {
    this->font.loadFromFile("Amatic.ttf");
    this->scorePlayer1.setFont(this->font);
    this->scorePlayer2.setFont(this->font);

    this->scorePlayer1.setCharacterSize(20);
    this->scorePlayer2.setCharacterSize(20);

    this->scorePlayer1.setString(to_string(this->player1->getScore()));
    this->scorePlayer2.setString(to_string(this->player2->getScore()));

    this->scorePlayer1.setFillColor(Color::White);
    this->scorePlayer2.setFillColor(Color::White);

}


void Game::keyInput(Keyboard::Key key) {
//pohyby W a S
    switch (key) {
        case Keyboard::W:
            if (player1->getPositionY() > 0) {
                player1->ascend();
            } else if (player2->getPositionY() > 0){
                player2->ascend();
            }
            break;
        case Keyboard::S:
            if (player1->getPositionY()+50 < height) {
                player1->descend();
            } else if (player2->getPositionY()+50 < height){
                player2->descend();
            }
            break;
        case Keyboard::R:
            if (pause)
            {
                this->ball->setStartPosX(0);
                this->ball->setStartPosY(0);
                player1->resetPosition();
                player2->resetPosition();
                player1->setScore(0);
                player2->setScore(0);
                pause = false;
            }
        default:
            break;
    }
}

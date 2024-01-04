//
// Created by adria on 4. 1. 2024.
//
#include <string>
#include "Game.h"

using namespace std;


Game::Game() {
    RenderWindow* window;
    drawAll(window);
    Play(window);
}

void Game::drawAll(RenderWindow *window) {
    this->ball = new Ball((this->width / 2), (this->height/2));
    this->player1 = new GamePlayer(0, (this->height / 2) - 22);
    this->player2 = new GamePlayer(width - 8, (this->height / 2) - 22);
    window->create(VideoMode(this->width, this->height), "Pong");
    window->setFramerateLimit(60);
    this->player1->render(window);
    this->player2->render(window);
    this->ball->draw(window, this->ball->getStartPosX(), this->ball->getStartPosY());

    this->setFont(window);
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

    this->scorePlayer1.setPosition((width/2) - 50, 5);
    this->scorePlayer2.setPosition((width/2) + 50, 5);

    window->draw(this->scorePlayer1);
    window->draw(this->scorePlayer2);


}

void Game::drawNew(RenderWindow *window, double x, double y) {
    window->clear();
    this->player1->render(window);
    this->player2->render(window);
    this->ball->draw(window, x, y);
    window->display();
}

void Game::Play(RenderWindow* window) {

    while(window->isOpen())
    {
        Event event;
        while(window->pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window->close();
            }
            if(event.type == Event::KeyPressed)
            {

            }
        }
        ball->updateMovementOfBall(this->player1, this->player2, window);
        drawNew(window, this->ball->getMovementX(), this->ball->getMovementY());
        if(this->ball->getPosition().x > window->getSize().x)
        {
            this->player1->plusScore();
            this->player1->resetPosition();
            this->player2->resetPosition();
            drawNewScore(window);
            this->ball->setPositions(this->player1->getGlobalBoundsOfPlayer().width + 10, (window->getSize().y / 2) - (this->ball->getBoundsOfBall().height / 2));
            this->ball->setMovementXPlus();
            this->ball->setMovementYMinus();

        }
        else if(this->ball->getPosition().x < 0)
        {
            this->player2->plusScore();
            this->player1->resetPosition();
            this->player2->resetPosition();
            drawNewScore(window);
            this->ball->setPositions(window->getSize().x - (this->player1->getGlobalBoundsOfPlayer().width - 10) , (window->getSize().y / 2) - (this->ball->getBoundsOfBall().height / 2));
            this->ball->setMovementXMinus();
            this->ball->setMovementYPLus();
        }

    }

}

void Game::drawNewScore(RenderWindow* window) {
    this->scorePlayer1.setString(to_string(this->player1->getScore()));
    this->scorePlayer2.setString(to_string(this->player2->getScore()));
    window->draw(this->scorePlayer1);
    window->draw(this->scorePlayer2);
    window->display();
}



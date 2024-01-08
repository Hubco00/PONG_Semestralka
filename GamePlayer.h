//
// Created by matej on 4. 1. 2024.
//

#ifndef PONG_SEMESTRALKA_GAMEPLAYER_H
#define PONG_SEMESTRALKA_GAMEPLAYER_H
#include "iostream"
#include "SFML/Graphics.hpp"

using namespace sf;

class GamePlayer {
private:
    double currentPositionX;
    double initialPositionX;
    double currentPositionY;
    double initialPositionY;
    int playerScore = 0;
    RectangleShape player;

public:
    //Konstruktor a destruktor
    GamePlayer(float startX, float startY);
    ~GamePlayer();

    //Getre ktore su cost kedze iba vytahuju data z premennych
    double getPositionX() const { return currentPositionX; };
    double getPositionY() const { return currentPositionY; };
    int getScore() const { return playerScore; };

    void move(float deltaX, float deltaY);
    void ascend();
    void descend();
    void render(RenderWindow* window);
    void resetPosition();
    FloatRect getGlobalBoundsOfPlayer();
    void resetScore();
    void setPlayerPosition(double posX, double posY);

    void setPlayerScore(int playerScore);

    // Seter
    void plusScore();

    void setCurrentPositions(double currentPositionX, double currentPositionY);


};




#endif //PONG_SEMESTRALKA_GAMEPLAYER_H

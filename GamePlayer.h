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
    Vector2f currentPosition;
    Vector2f initialPosition;
    int playerScore = 0;

public:
    //Konstruktor a destruktor
    GamePlayer(float startX, float startY);
    ~GamePlayer();

    //Getre ktore su cost kedze iba vytahuju data z premennych
    Vector2f getPosition() const { return currentPosition; };
    int getScore() const { return playerScore; };

    void move(float deltaX, float deltaY);
    void ascend();
    void descend();
    void render(RenderWindow* window);
    void resetPosition();

    // Seter
    void updateScore(int newScore) { playerScore = newScore; }
};




#endif //PONG_SEMESTRALKA_GAMEPLAYER_H

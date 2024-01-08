//
// Created by adria on 4. 1. 2024.
//
#include <string>
#include "Game.h"

using namespace std;
Game::Game() {
    RenderWindow window;
    this->end = false;
    drawAll(&window);
    this->socket.setBlocking(false);
    std::thread conT(&Game::connect, this);
    conT.join();

    listeningThread = std::thread(&Game::listen,this);

    Play(&window);
}

Game::~Game() {
   // delete this->con;
    delete this->ball;
    delete this->secondBall;
}

void Game::drawAll(RenderWindow *window) {
    window->create(VideoMode(this->width, this->height), "Pong");
    window->setFramerateLimit(60);
    this->ball = new Ball((this->width / 2), (this->height/2));
    this->player1 = new GamePlayer(0, (this->height / 2) - 22);
    this->player2 = new GamePlayer(width - 8, (this->height / 2) - 22);
    this->player1->render(window);
    this->player2->render(window);
    this->ball->draw(window, this->ball->getPosX(), this->ball->getPosY());

    this->secondBall = new Ball((this->width / 2), (this->height/2));

    this->setFont(window);
    window->display();
}

void Game::setFont(RenderWindow *window) {
    if(!this->font.loadFromFile("../arial.ttf"))
    {
        cout << "NONO" << endl;
    }
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
    this->scorePlayer1.setString(to_string(this->player1->getScore()));
    this->scorePlayer2.setString(to_string(this->player2->getScore()));
    window->draw(this->scorePlayer1);
    window->draw(this->scorePlayer2);
    window->display();
}

void Game::Play(RenderWindow* window) {


    while(window->isOpen())
    {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed){
                window->close();
            }
            if (event.type == Event::KeyPressed){
                keyInput(event.key.code);
            }
        }
        if(!end) {

            if (this->packetTypes == PacketTypes::SERVER) {
                this->send(PacketTypes::BALL, (float) this->ball->getPosX(), (float) this->ball->getPosY());
                ball->updateMovementOfBall(this->player1, this->player2, window);
            }

            drawNew(window, this->ball->getPosX(), this->ball->getPosY());

            if (this->ball->getPosition().x > window->getSize().x) {
                this->player1->plusScore();
                this->send(PacketTypes::SCORE, this->player1->getScore(), this->player2->getScore());
                //this->con->sendPacketScoreInfo(this->player1->getScore());
                this->player1->resetPosition();
                this->player2->resetPosition();
                this->send(PacketTypes::END, this->player1->getPositionY(), this->player2->getPositionY());

                this->ball->redrawToPos(this->player1->getGlobalBoundsOfPlayer().width + 10,
                                        (window->getSize().y / 2) -
                                        (this->ball->getBoundsOfBall().height / 2));


            } else if (this->ball->getPosition().x < 0) {
                this->player2->plusScore();
                this->send(PacketTypes::SCORE, this->player1->getScore(), this->player2->getScore());
                this->player1->resetPosition();
                this->player2->resetPosition();
                this->send(PacketTypes::END, this->player1->getPositionY(), this->player2->getPositionY());
                this->ball->redrawToPos(window->getSize().x -
                                                (this->player1->getGlobalBoundsOfPlayer().width + 10),
                                        (window->getSize().y / 2) -
                                        (this->ball->getBoundsOfBall().height / 2));
            }

        }
    }
    listeningThread.join();
}

void Game::drawNewScore(RenderWindow* window) {

    window->display();
}

void Game::keyInput(Keyboard::Key key) {
//pohyby W a S
    switch (key) {
        case Keyboard::W:
            if (this->packetTypes == PacketTypes::SERVER && player1->getPositionY() > 0) {
                player1->ascend();
                this->send(PacketTypes::PLAYER,0,player1->getPositionY());


            } else if (this->packetTypes == PacketTypes::CLIENT && player2->getPositionY() > 0){
                player2->ascend();
                this->send(PacketTypes::PLAYER,width-8,player2->getPositionY());

            }
            break;
        case Keyboard::S:
            if (this->packetTypes == PacketTypes::SERVER && player1->getPositionY()+50 < height) {
                player1->descend();
                this->send(PacketTypes::PLAYER,0,player1->getPositionY());

            } else if (this->packetTypes == PacketTypes::CLIENT && player2->getPositionY()+50 < height){
                player2->descend();
                this->send(PacketTypes::PLAYER,width-8,player2->getPositionY());
            }
            break;
        case Keyboard::R:
            if (this->end)
            {
                if(this->packetTypes == PacketTypes::SERVER)
                {
                    this->send(PacketTypes::PLAYER,0,0);
                } else
                {
                    this->send(PacketTypes::PLAYER,width-8,0);
                }

                this->ball->setPosX(0);
                this->ball->setPosY(0);
                player1->resetPosition();
                player2->resetPosition();
                player1->resetScore();
                player2->resetScore();
                this->end = false;
            }
        default:
            break;
    }
}

void Game::connect() {

    cout << "Enter 's' to be a server and 'c' to be a client." << endl;
    string input;
    cin >> input;

    if (input == "s") {
        TcpListener listener;
        if (listener.listen(PORT) != Socket::Done) {
            cerr << "Server failed to listen on port." << endl;
            return;
        }

        cout << "Server started. Waiting for client." << endl;
        this->packetTypes = PacketTypes::SERVER;
        if (listener.accept(this->socket) != Socket::Done) {
            cerr << "Failed to accept client connection." << endl;
            return;
        }

        cout << "Client connected." << endl;
        this->listening = true;
    } else if (input == "c") {
        cout << "Enter IP address of your host: ";
        string hostIP;
        cin >> hostIP;

        this->packetTypes = PacketTypes::CLIENT;
        if (this->socket.connect(IpAddress(hostIP), PORT)) {
            cout << "Connected to server." << endl;
            this->listening = true;
        } else {
            cerr << "Failed to connect to server." << endl;
            this->listening = false;
        }
    }

}
void Game::listen() {

    Packet packet;
    while (listening){
        if (socket.receive(packet) == Socket::Done){
            if (this->packetTypes == PacketTypes::SERVER) {
                extractFromPackets(packet, this->player2, ball);
            } else {
                extractFromPackets(packet, this->player1, ball);
            }
        }
    }
}

void Game::extractFromPackets(Packet packet, GamePlayer* player, Ball* ball)
{
    int packetType;
    float firstPacketInfo, secondPacketInfo;
    packet >> packetType >> firstPacketInfo >> secondPacketInfo;
    switch (packetType) {
        case 3:
            player->setCurrentPositions((double)firstPacketInfo, (double)secondPacketInfo);
            break;
        case 4:
            this->player1->setPlayerScore(firstPacketInfo);
            this->player2->setPlayerScore(secondPacketInfo);
            break;
        case 5:
            ball->redrawToPos((double)firstPacketInfo, (double)secondPacketInfo);
            break;
        case 6:
            this->player1->setCurrentPositions(0, (double)firstPacketInfo);
            this->player2->setCurrentPositions(width-8, (double)secondPacketInfo);
    }

}

void Game::send(PacketTypes packetTypes, float firstInfo, float secondInfo)
{
    Packet packet;
    packet << (int)packetTypes << firstInfo << secondInfo;
    socket.send(packet);
}



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

    std::thread conT(&Game::connect, this);
    conT.join();


    std::thread listenT;
    if(this->packetTypes == PacketTypes::SERVER)
    {
        listenT = std::thread(&Game::listen,this,this->player2);
    }
    else
    {
        listenT = std::thread(&Game::listen,this,this->player1);
    }

    listenT.join();

    Play(&window);
}

Game::~Game() {
    delete this->con;
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
                this->con->sendPacketBallInfo(PacketTypes::BALL, (float) this->ball->getPosX(), (float) this->ball->getPosY());
                ball->updateMovementOfBall(this->player1, this->player2, window);
            }

            drawNew(window, this->ball->getPosX(), this->ball->getPosY());
            if (this->packetTypes == PacketTypes::SERVER)
            {
                if (this->ball->getPosition().x > window->getSize().x) {
                    this->player1->plusScore();

                    this->con->sendPacketScoreInfo(this->player1->getScore());
                    this->player1->resetPosition();
                    this->player2->resetPosition();

                    this->ball->redrawToPos(this->player1->getGlobalBoundsOfPlayer().width + 10,
                                            (window->getSize().y / 2) -
                                            (this->ball->getBoundsOfBall().height / 2));


                } else if (this->ball->getPosition().x < 0) {
                    this->player2->plusScore();
                    this->con->sendPacketScoreInfo(this->player2->getScore());
                    this->player1->resetPosition();
                    this->player2->resetPosition();
                    this->ball->redrawToPos(window->getSize().x -
                                                    (this->player1->getGlobalBoundsOfPlayer().width + 10),
                                            (window->getSize().y / 2) -
                                            (this->ball->getBoundsOfBall().height / 2));
                }
            }
            else
            {
                this->con->recievePacketScoreInfo();
                this->scorePlayer1.setString(to_string(player1->getScore()));
                this->scorePlayer2.setString(to_string(player2->getScore()));
            }
        }
    }

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
                this->con->sendPacketPlayerInfo(PacketTypes::PLAYER,player1->getPositionY());


            } else if (this->packetTypes == PacketTypes::CLIENT && player2->getPositionY() > 0){
                player2->ascend();
                this->con->sendPacketPlayerInfo(PacketTypes::PLAYER,player2->getPositionY());

            }
            break;
        case Keyboard::S:
            if (this->packetTypes == PacketTypes::SERVER && player1->getPositionY()+50 < height) {
                player1->descend();
                this->con->sendPacketPlayerInfo(PacketTypes::PLAYER,player1->getPositionY());

            } else if (this->packetTypes == PacketTypes::CLIENT && player2->getPositionY()+50 < height){
                player2->descend();
                this->con->sendPacketPlayerInfo(PacketTypes::PLAYER,player2->getPositionY());
            }
            break;
        case Keyboard::R:
            if (this->end)
            {
                this->con->sendPacketPlayerInfo(PacketTypes::PLAYER,0);
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
    unique_lock<std::mutex> loc(this->mutex);
    this->con = new Connection(PORT);

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
        if (listener.accept(this->con->getSocket()) != Socket::Done) {
            cerr << "Failed to accept client connection." << endl;
            return;
        }

        cout << "Client connected." << endl;
        this->con->setConnected(true);
        loc.unlock();
    } else if (input == "c") {
        cout << "Enter IP address of your host: ";
        string hostIP;
        cin >> hostIP;

        this->packetTypes = PacketTypes::CLIENT;
        if (con->connect(IpAddress(hostIP))) {
            cout << "Connected to server." << endl;
            this->con->setConnected(true);
            loc.unlock();
        } else {
            cerr << "Failed to connect to server." << endl;
            this->con->setConnected(false);
            loc.unlock();
        }
    }
}
void Game::listen(GamePlayer* player) {

    Packet packet;
    while(this->con->getConnected())
    {
        unique_lock<std::mutex> loc(mutex);
        if(this->con->getSocket().receive(packet) == Socket::Done)
        {
            this->con->extractFromPackets(packet, player, ball);
            loc.unlock();
        }
    }
}



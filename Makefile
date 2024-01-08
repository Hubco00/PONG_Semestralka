output: main.o Ball.o GamePlayer.o Game.o
	g++ main.o Ball.o GamePlayer.o Game.o -o output

main.o : main.cpp
	g++ -c main.cpp
Ball.o : Ball.cpp Ball.h
	g++ -c Ball.cpp
GamePlayer.o : GamePlayer.cpp GamePlayer.h
	g++ -c GamePlayercpp
Game.o: Game.cpp GamePlayer.h
	g++ -c Game.cpp

clean:
	rm *.o output
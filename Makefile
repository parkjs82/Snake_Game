CC = g++


all:
	g++ -std=c++11 -o snake_game main.cpp MakeField.cpp Snake.cpp Score.cpp -lncursesw

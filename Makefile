CC = g++


all:
	g++ -std=c++11 -o snakegame main.cpp MakeField.cpp Snake.cpp Score.cpp -lncursesw

CC = g++


all:
	g++ -std=c++11 -o main main.cpp MakeField.cpp Snake.cpp -lncursesw

#!/bin/zsh
g++ -Wall -g -std=c++0x -c "imageloader.cpp" -o "imageloader.o"
g++ -Wall -g -std=c++0x -c "main.cpp" -o "main.o"
g++ "imageloader.o" -lglut -lGL -lpthread "main.o" -lglut -lGLU -lGL -lpthread -o "system"

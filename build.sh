#!/bin/zsh
clear
rm system
g++ -Wall -g -std=c++0x -c "imageloader.cpp" -o "imageloader.o"
g++ -Wall -g -std=c++0x -c "planet.cpp" -o "planet.o"
g++ -Wall -g -std=c++0x -c "solarsystem.cpp" -o "solarsystem.o"
g++ -Wall -g -std=c++0x -c "main.cpp" -o "main.o"
g++ "imageloader.o" -lglut -lGL -lpthread "planet.o" -lglut -lGL -lpthread "solarsystem.o" -lglut -lGL -lpthread "main.o" -lglut -lGLU -lGL -lpthread -o "system"

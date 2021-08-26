#!/bin/sh
g++ -c main.cpp
g++ main.o -o main -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio
./main


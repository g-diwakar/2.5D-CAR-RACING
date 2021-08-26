#ifndef PARAMETERS_H
#define PARAMETERS_H

#include<SFML/Graphics.hpp>
using namespace sf;

//Game map
const int width=1024;
const int height=760;
const int roadW=2500;
const int segl=200;//segment length
const float camD=0.85;//camera depth


//for side pictures
Texture t[14];
Sprite pictures[14];

//coin
Texture tcoin;
Sprite scoin;

//bot
Texture tbot[10];
Sprite sbot[10];


#endif
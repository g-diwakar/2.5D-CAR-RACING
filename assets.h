#ifndef ASSETS_H
#define ASSETS_H

#include<SFML/Graphics.hpp>
#include<string>
#include"parameters.h"
#include"gamemap.h"

class Assets
{
private:
	sf::Texture tbackground;
	sf::Sprite background;
public:
	void drawBackground(sf::RenderWindow&);
	void loadPictures(Construct&);
	void loadCoin(Construct&);
	void loadBot();
};

void Assets::drawBackground(sf::RenderWindow &app)
{
	tbackground.loadFromFile("Images/bg.png");
	tbackground.setRepeated(true);

	background.setTexture(tbackground);
	background.setTextureRect(IntRect(0,0,5000,1000));
	background.setPosition(-1500,-410);

	app.draw(background);
}

void Assets::loadPictures(Construct& c)
{
	for(int i=1;i<14;i++)
	{		
		t[i].loadFromFile("Images/"+std::to_string(i)+".png");		
		t[i].setSmooth(true);
		pictures[i].setTexture(t[i]);
	}

	
	c.constructPictures(pictures);
}

void Assets::loadCoin(Construct &c)
{
	tcoin.loadFromFile("Images/coin.png");
	tcoin.setSmooth(true);

	scoin.setTexture(tcoin);

	c.constructCoin(scoin);
}

void Assets::loadBot()
{
	for(int i=0;i<6;i++)
	{
		tbot[i].loadFromFile("Images/Obstacles/"+std::to_string(i)+".png");
		tbot[i].setSmooth(true);

		sbot[i].setTexture(tbot[i]);

	}
}
#endif
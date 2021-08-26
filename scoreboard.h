#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
#include"parameters.h"
class ScoreBoard
{
private:
	sf::Font font;
	sf::Text score_text;
	sf::Texture health_foto;
	sf::Sprite health;
	sf::RectangleShape rect[2];

	int health_percentage;
	int score;

public:
	void initialize()
	{
		loadScoreFont();
		loadHealthBar();
		score=0;
		health_percentage=100;
	}
	void loadScoreFont();
	void loadHealthBar();
	void drawHealthBar(sf::RenderWindow&);
	void updateScore(int);
	void updateHealthPercentage(int);
	int getScore();
	int getHealthPercentage();
};

void ScoreBoard::loadScoreFont()
{
	font.loadFromFile("Fonts/SFAtarianSystem.ttf");
	
	score_text.setPosition(width*0.9,height/100);
	score_text.setFont(font);
	score_text.setFillColor(sf::Color::Green);
	score_text.setOutlineColor(sf::Color::Black);
	score_text.setCharacterSize(30);
	score_text.setStyle(sf::Text::Bold);
	score_text.setOutlineThickness(2);
}

void ScoreBoard::loadHealthBar()
{
	for(int i=0;i<2;i++)
	{
		rect[i].setPosition(width/2,height/100+20);
		rect[i].setSize(Vector2f(100,30));
		
		i==0?rect[i].setFillColor(sf::Color(0,0,0,150)):rect[i].setFillColor(sf::Color::Green);

	}

	health_foto.loadFromFile("Images/healthPicture.png");
	health.setTexture(health_foto);
	health.setPosition(width/2-rect[1].getGlobalBounds().width/2,height/100+20-rect[1].getGlobalBounds().height/2);

}

void ScoreBoard::drawHealthBar(sf::RenderWindow& app)
{
	
	if(health_percentage>=0)
		rect[1].setSize(Vector2f(health_percentage,30));

	if(health_percentage>75)
		{rect[1].setFillColor(sf::Color::Green);}
	else if(health_percentage>50 && health_percentage <=75)
		rect[1].setFillColor(sf::Color(103,255,153));
	else if (health_percentage>25 && health_percentage <=50)
		rect[1].setFillColor(sf::Color(255,102,102));
	else if (health_percentage>0 && health_percentage <=25)
		rect[1].setFillColor(sf::Color::Red);

	app.draw(rect[0]);
	app.draw(rect[1]);
	score_text.setString("SCORE\n\n"+std::to_string(score));
	app.draw(health);
	app.draw(score_text);
}

void ScoreBoard::updateScore(int s)
{
	score+=s;
}

void ScoreBoard::updateHealthPercentage(int n)
{
	health_percentage+=n;
}

int ScoreBoard::getScore()
{
	return score;
}

int ScoreBoard::getHealthPercentage()
{
	return health_percentage;
}

#endif
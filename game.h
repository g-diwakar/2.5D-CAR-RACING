#ifndef GAME_H
#define GAME_H

#include"gamemap.h"
#include"parameters.h"
#include"menu.h"
#include"sound.h"
#include"scoreboard.h"
#include"assets.h"

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>


using namespace sf;



class DrawQuad
{
private: 
	ConvexShape shape;
public:
	DrawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
	{
		shape.setPointCount(4);
		shape.setFillColor(c);
		shape.setPoint(0,Vector2f(x1-w1,y1));//left point of previous grid
		shape.setPoint(1,Vector2f(x2-w2,y2));//left point of current grid
		shape.setPoint(2,Vector2f(x2+w2,y2));//right point of current grid
		shape.setPoint(3,Vector2f(x1+w1,y1));//right point of previous grid
		w.draw(shape);
	}

	~DrawQuad() {}

};

class Game
{
private:
	int posZ,posX,N,startPos;
	int check_pos=0;
	int speed;
	bool player_alive=false;
	bool menu_state=true;
	
	//instantiating SFML classes
	RenderWindow app;
	Sprite player;
	Texture playerCar;
	CircleShape vplayer;

	//instantiating user defined classes 
	Construct c;
	Menu menu;
	ScoreBoard sboard;
	GameSound gsound;
	Assets asset;
public:
	Game(){
		app.create(VideoMode(width,height),"VROOM - VROOM",Style::Close);
		app.setFramerateLimit(60);
		speed=1;
	}
	~Game(){}

	
	void run();

	void handlePlayerInputs(Event& e);

	void drawRoad();
	void drawPictures();
	void loadPlayerCar();
	void collision();
	void drawGameOverState();
	void initialize();
	

	void update();
	
};

//initializing the different classes and parameters
void Game::initialize()
{
	c.constructGrids();

	posZ=0;
	posX=0;
	N=grids.size();

	startPos=0;
	sboard.initialize();
	gsound.loadSound();
	asset.loadPictures(c);
	asset.loadCoin(c);
	asset.loadBot();
	gsound.playSound(3);

}

//main loop where the game runs
void Game::run()
{
	initialize();
	while (app.isOpen())
	{
		
		Event e;
		handlePlayerInputs(e);
		
		if (player_alive)
		{
		 	collision();
		}
		

		app.clear();

		update();

		app.display();
	}
}

//this handles every inputs given by the user
void Game::handlePlayerInputs(Event& e)
{
	app.setKeyRepeatEnabled(true);

	while (app.pollEvent(e))
	{
		if(e.type==Event::Closed)
			app.close();
	}
	if (menu_state)
	{
		menu.handleInputs(app,e,player_alive,menu_state);
	}
	if (player_alive)
	{
		
		if(Keyboard::isKeyPressed(Keyboard::Up)) 
			{
				posZ+=speed*200;
			}
		if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) 
			{
				posX+=50;
			}
		if(Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
			{ 
				posX-=50;
			}
	}
	if (!player_alive && !menu_state)
	{
		if(Keyboard::isKeyPressed(Keyboard::Return)) 
		{
			if(app.waitEvent(e))
			{
				player_alive=false;
				menu_state=true;
				grids.clear();
				initialize();
			}
		}
	}

	//bounding the car to the camera position
	while (posZ>=N*segl) posZ-=N*segl;

	//finding out the current position of grid
	startPos=posZ/segl;
}


void Game::drawRoad()
{
	int camH = 1500;
	float x=0, dx=0;
	int maxy=height;

	///draw road////

	for(int n=startPos; n<startPos+300;n++)
	{
		Grid &g=grids[n%N];
		g.project(posX-x,camH,posZ-(n>=N?N*segl:0));
		x+=dx;
		dx+=g.getCurve();

		
		if (g.getY()>=maxy) continue;
		maxy=g.getY();
		

		Color grass=(n/3)%2?Color(16,200,16):Color(0,154,0);
		Color rumble=(n/3)%2?Color(255,255,255):Color(0,0,0);
		Color marking=(n/3)%2?Color(255,255,255):Color(105,105,105);
		Color road=(n/3)%2?Color(107,107,107):Color(105,105,105);

		Grid p= grids[(n-1)%N];//previous grid
	
		DrawQuad env(app,grass,0,p.getY(),width,0,g.getY(),width);
		DrawQuad side(app,rumble,p.getX(),p.getY(),p.getW()*1.1,g.getX(),g.getY(),g.getW()*1.1);
		DrawQuad baato1(app, road, p.getX(), p.getY(), p.getW(), g.getX(), g.getY(), g.getW());
		DrawQuad mark(app,marking,p.getX(), p.getY(), p.getW()*0.35, g.getX(), g.getY(), g.getW()*0.35);
		DrawQuad baato2(app, road, p.getX(), p.getY(), p.getW()*0.3, g.getX(), g.getY(), g.getW()*0.3);

	}
}

//draw pictures coin and bot
void Game::drawPictures() 
{
	for(int n=startPos+300;n>startPos;n--)
	{
		grids[n%N].setPictures(app);
		grids[n%N].setCoin(app);
		grids[n%N].setBot(app);

	}
}

void Game::loadPlayerCar()
{
	
	playerCar.loadFromFile("Images/CarImage.png");

	
	player.setTexture(playerCar);
	player.setPosition(width/2-player.getGlobalBounds().width/2,height-player.getGlobalBounds().height*1.5);
	
	vplayer.setRadius(50.f);
	vplayer.setPosition(player.getPosition().x+50,player.getPosition().y);

	app.draw(player);
}

void Game::collision()
{

	if (grids[startPos+10].getCoinBounds().intersects(vplayer.getGlobalBounds()))
	{
		sboard.updateScore(5);
		gsound.playSound(0);		
	}
	if (grids[startPos+10].getBotBounds().intersects(vplayer.getGlobalBounds()))
	{
		if((startPos+10-check_pos)>10 || (startPos+10-check_pos)<0)
		{
			if (sboard.getHealthPercentage()>=80) sboard.updateHealthPercentage(-5);
			if(sboard.getHealthPercentage()>=50 && sboard.getHealthPercentage()<80) sboard.updateHealthPercentage(-10);
			if(sboard.getHealthPercentage()>=20 && sboard.getHealthPercentage()<50) sboard.updateHealthPercentage(-15);
			if(sboard.getHealthPercentage()>=10 && sboard.getHealthPercentage()<20) sboard.updateHealthPercentage(-5);
			if(sboard.getHealthPercentage()>0 && sboard.getHealthPercentage()<10) 
				{
					int check_health=sboard.getHealthPercentage();
					sboard.updateHealthPercentage(-check_health);
				}
			check_pos=startPos+10;
			gsound.stopSound(0);
			gsound.playSound(1);
		}
	}

	if(sboard.getHealthPercentage()<=0)
	{
		player_alive=false;
		int check_score=sboard.getScore();
		menu.checkHighScore(check_score);
		menu.HighScore::loadAssets();
		gsound.stopSound(0);
		gsound.stopSound(1);
		gsound.playSound(2);
	}
}

void Game::drawGameOverState()
{
	Font f;
	Text game_over;
	FloatRect gameRect=game_over.getLocalBounds();

	f.loadFromFile("Fonts/raider.ttf");
	game_over.setFont(f);
	game_over.setOrigin(gameRect.left+gameRect.width/2.0f,gameRect.top+gameRect.height/2.0f);
	game_over.setPosition(width/2-400,height/2-200);
	game_over.setFillColor(Color(155,34,48));
	game_over.setString("GAME OVER\nYOUR SCORE:"+std::to_string(sboard.getScore()));
	game_over.setCharacterSize(100);
	app.draw(game_over);
	

}


//update the changes made to the game screen

void Game::update()
{

if (!menu_state)
	{
		asset.drawBackground(app);
		drawRoad();
		drawPictures(); //draw side pictures,coin and bot
	}
if(player_alive)
{
	sboard.drawHealthBar(app);
	c.constructBot(sbot);
	loadPlayerCar();
}	
if(!player_alive && !menu_state)
{
	drawGameOverState();
}

if(menu_state)
{
	menu.drawMenu(app);
}	
	
	
}




#endif

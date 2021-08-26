#ifndef GAMEMAP_H
#define GAMEMAP_H

#include"parameters.h"

#include<cmath>
#include<SFML/Graphics.hpp>
using namespace sf;

#include<iostream>

class Construct;

class Grid
{
private:
	float x,y,z; //3d center of line 
	float X,Y,W; //screen coordiante
	float curve,scale;
	float pictureX;
	float coinX;
	float botX;
	bool draw_bot=true;

	Sprite sprite;
	FloatRect texture_rect;
	Sprite coin;
	FloatRect coin_bounds;
	Sprite bot;
	FloatRect bot_bounds;

	

public:
	Grid() {curve=x=y=z=0;}
	~Grid(){}

	//from world to screen coordintates
	void project (int camX, int camY, int camZ)
	{
		scale =camD/(z-camZ);
		X=(1+scale*(x-camX))*width/2;
		Y=(1-scale*(y-camY))*height/2;
		W=scale*roadW*width/2;
	}

	void setPictures(RenderWindow &app)
	{
		Sprite s= sprite;

		int w=s.getTextureRect().width;
		int h=s.getTextureRect().height;

		float setX= X + scale*pictureX*width/2;
		float setY=Y;
		float setW=w*W/266;
		float setH=h*W/266;

		setX+=setW*pictureX;
		setY-=setH;

		s.setTextureRect(IntRect(0,0,w,h-h/setH));
		s.setScale(setW/w,setH/h);
		s.setPosition(setX,setY);

		app.draw(s);
	}

	void setCoin(RenderWindow &app)
	{
		Sprite s= coin;
		int w=s.getTextureRect().width;
		int h=s.getTextureRect().height;

		float setX=X+scale*coinX*width/2;
		float setY=Y-4;
		float setW=w*W/266;
		float setH=h*W/266;

		setX+=setW*coinX;
		setY-=setH;

		s.setTextureRect(IntRect(0,0,w,h-h/setH));
		s.setScale(setW/w,setH/h);
		s.setPosition(setX,setY);

		coin_bounds=s.getGlobalBounds();

		app.draw(s);
	}

	void setBot(RenderWindow &app)
	{
		if(draw_bot)
		{
			Sprite s;
			s=bot;
			int w=s.getTextureRect().width;
			int h=s.getTextureRect().height;

			float setX=X+scale*botX*width/2;
			float setY=Y;

			float setW=w*W/266;
			float setH=h*W/266;

			setX+=setW*botX;
			setY-=setH;

			s.setTextureRect(IntRect(0,0,w,h-h/setH));
			s.setScale(setW/w,setH/h);
			s.setPosition(setX,setY);

			bot_bounds=s.getGlobalBounds();
			app.draw(s);
		}

	}

	FloatRect getBotBounds()
	{
		return bot_bounds;
	}

	FloatRect getCoinBounds()
	{
		return coin_bounds;
	}

	float getz(){return z;}
	float gety(){return y;}
	float getX(){return X;}
	float getY(){return Y;}
	float getW(){return W;}
	float getCurve(){return curve;}
	
	friend class Construct;
};

std::vector<Grid> grids;

class Construct 
{
private:
	int bot_position[18];
	int reset;
public:
	Construct()
	{
		
		for(int i=0;i<18;i++)
		{
			bot_position[i]=300+i*100;
		}
		
	}
	void constructGrids()
	{
		for(int i=0; i<3000; i++)
		{
			Grid grid;
			grid.z = i*segl;

			if(i>300 && i<700) grid.curve=0.5;

			if(i>750 && i<1000) grid.curve=-0.5;

			if(i>1200 && i<1500) grid.curve=0.8;

			if(i>1500 && i<1750) grid.curve=-0.8;

			if(i>1750 && i<2000) grid.curve=0.7;

			if(i>2200 && i<2480) grid.curve=-0.9;

			if(i>2500 && i<2950) grid.curve=0.9;



			grids.push_back(grid);
		}
	}

	void constructPictures(Sprite ob[])
	{
		for(int  i=0;i<3000;i++)
		{
			if(i>0 && i<500 && i%15==0)
			{
				grids[i].pictureX=1.1;
				grids[i].sprite=ob[4];
			}
			if(i>0&& i<500 && i%10==0)
			{
				grids[i].pictureX=-1.5;
				grids[i].sprite=ob[1];
			}
			if(i>500 && i<1000 && i%15==0)
			{
				grids[i].pictureX=-2.1;
				grids[i].sprite=ob[9];
			}

			if(i>500&& i<1000 && i%10==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[1];
			}

			if(i>1000 && i<1200 && i%15==0)
			{
				grids[i].pictureX=-1.5;
				grids[i].sprite=ob[10];
			}

			if(i>1000 && i<1200 && i%10==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[12];
			}

			if(i>1250 && i<1500 && i%20==0)
			{
				grids[i].pictureX=-2.5;
				grids[i].sprite=ob[3];
			}
			if(i>1000 && i<1550 && i%25==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[11];
			}

			if(i>1600 && i<2000 && i%20==0)
			{
				grids[i].pictureX=-2.5;
				grids[i].sprite=ob[11];
			}

			if(i>1600 && i<2000 && i%30==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[3];
			}

			if(i>2000 && i<2500 && i%20==0)
			{
				grids[i].pictureX=-2.5;
				grids[i].sprite=ob[2];
			}

			if(i>2000 && i<2500 && i%23==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[8];
			}
			if(i>2500 && i<3000 && i%20==0)
			{
				grids[i].pictureX=-2.5;
				grids[i].sprite=ob[8];
			}

			if(i>2500 && i<3000 && i%23==0)
			{
				grids[i].pictureX=1.5;
				grids[i].sprite=ob[7];
			}


		}
	}

	void constructCoin(Sprite &coins)
	{
		for(int i=0;i<3000;i++)
		{
			if(i>150 && (i+21)%59==0)
			{
				grids[i].coinX=0.5;
				grids[i].coin=coins;
			}
			if(i>150 && i%59==0)
            {	grids[i].coinX=-2.5; 
            	grids[i].coin=coins;
            }
        	if(i>101 && (i-21)%49==0)
            {
            	grids[i].coinX=2.2 ;
            	grids[i].coin=coins;
            }
		}
	}

	void constructBot(Sprite ob[])
	{

		for(int i=0;i<18;i++)
		{
			
			updateBot(i);
			//bounding the bot to the grid lines
			while(bot_position[i]<=0) bot_position[i]+=3000;
			while(bot_position[i]>3000) bot_position[i]-=3000;

			if (i%2==0)
			{
				if(i<6)
				{
					grids[bot_position[i]].botX=0.4;
					grids[bot_position[i]].bot=ob[i];
					grids[bot_position[i]].draw_bot=true;
				}

				if(i>=6 && i<12)
				{
					grids[bot_position[i]].botX=-1;
					grids[bot_position[i]].bot=ob[i-6];
					grids[bot_position[i]].draw_bot=true;
				}

				if(i>=12)
				{
					grids[bot_position[i]].botX=-0.6;
					grids[bot_position[i]].bot=ob[i-12];
					grids[bot_position[i]].draw_bot=true;
				}

			}

			else
			{
				if(i<6)
				{
					grids[bot_position[i]].botX=-0.6;
					grids[bot_position[i]].bot=ob[i];
					grids[bot_position[i]].draw_bot=true;
				}
				
				if(i>=6 && i<12)
				{
					grids[bot_position[i]].botX=0.4;
					grids[bot_position[i]].bot=ob[i-6];
					grids[bot_position[i]].draw_bot=true;

				}
				
				if(i>=12)
				{
					grids[bot_position[i]].botX=0.4;
					grids[bot_position[i]].bot=ob[i-12];
					grids[bot_position[i]].draw_bot=true;

				}

			}
			
			
		}
		
		
	}

	void updateBot(int n)
	{
		grids[bot_position[n]].draw_bot=false;
		bot_position[n]-=1;
	}

};




#endif

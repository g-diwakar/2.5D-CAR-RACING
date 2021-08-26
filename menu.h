#ifndef MENU_H
#define MENU_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>

class Instructions
{
protected:
	sf::Text text_instruction;
	sf::Font font_instruction;
	bool state=false;
public:
	void loadAssets()
	{
		font_instruction.loadFromFile("Fonts/the-heart-of.ttf");
		text_instruction.setFont(font_instruction);

		text_instruction.setString("Use \"Arrow Up\" to Move Forward \nUse \"Arrow Right\" and \"Arrow left\" to \nMove Right and Left\n\nCollect as many coins avoiding collision\nwith moving vehicles before\nyour health decreases to ZERO\n!!!!Be ready to play and enjoy the game!!!! ");
		text_instruction.setFillColor(sf::Color(0,0,0));
		text_instruction.setCharacterSize(50);
		text_instruction.setPosition(10.f,150.f);
	}
};

class About
{
protected:
	sf::Text text_about;
	sf::Font font_about;
	bool state=false;

public:
	void loadAssets()
	{
		font_about.loadFromFile("Fonts/the-heart-of.ttf");
		text_about.setFont(font_about);

		text_about.setString("Game developed as an OOP project at third semester by\n\n1. Diwakar Gyawali (PUL076BCT024)\n\n2. Manoj Khatri (PUL076BCT034)\n\n3. Prajjwal Pandey (PUL076BCT044)");
		text_about.setPosition(10.f,100.f);
		text_about.setFillColor(Color(0,0,0));
		text_about.setCharacterSize(35);
	}
};
class HighScore
{
protected:
	sf::Text text_highscore[5];
	sf::Font font_highscore;
	bool state=false;
	int highscore[5];
public:
	void checkHighScore(int n)
	{
		int temp=0;
		int temp1=0;
		int check=0;
		bool changes=false;

		for(int i=0;i<5;i++)
			highscore[i]=0;

		std::ifstream ifile("score.txt");
		if (ifile)
			for(int i=0;i<5;i++)
			{
				ifile>>highscore[i];
			}

		for(int i=0;i<5;i++)
		{
			if(highscore[i]<n)
			{
				temp=highscore[i];
				check=i+1;
				highscore[i]=n;
				changes=true;
				break;
			}
		}

		ifile.close();
		if (changes)
		{
			for(int i=check;i<5;i++)
			{
				temp1=highscore[i];
				highscore[i]=temp;
				temp=temp1;
			}
		}
		std::ofstream ofile("score.txt");
		for(int i=0;i<5;i++)
			ofile<<highscore[i]<<std::endl;
		ofile.close();
	}

	void loadAssets()
	{
		std::ifstream ifile("score.txt");
		if (ifile)
			for(int i=0;i<5;i++)
			{
				ifile>>highscore[i];
			}
		ifile.close();
		font_highscore.loadFromFile("Fonts/the-heart-of.ttf");

		for(int i=0;i<5;i++)
		{
			text_highscore[i].setFont(font_highscore);
			text_highscore[i].setString(std::to_string(i+1)+".  "+std::to_string(highscore[i]));
			text_highscore[i].setFillColor(Color(0,0,0));
			text_highscore[i].setPosition(150,100+100*i);
			text_highscore[i].setCharacterSize(50);
		}
	}

};
class Menu:public Instructions,public About,public HighScore
{
	private:
	sf::Text text[5];
	sf::Font font;

	sf::Texture tbgmenu;
	sf::Sprite sbgmenu;

	sf::Texture tmenubg;
	sf::Sprite smenubg;

	int itemIndex;
	bool state;

public:
	Menu()
	{
		loadAssets();
		state=true;
		itemIndex=0;
	}
	void loadAssets();

	void moveUp();
	void moveDown();
	void handleInputs(sf::RenderWindow&,sf::Event&, bool&, bool&);
	void drawMenu(sf::RenderWindow&);
};

void Menu::loadAssets()
{
	Instructions::loadAssets();
	About::loadAssets();
	HighScore::loadAssets();


	font.loadFromFile("Fonts/vtks-revolt.ttf");

	tbgmenu.loadFromFile("Images/menubg.png");
	tbgmenu.setRepeated(true);
	sbgmenu.setTexture(tbgmenu);

	tmenubg.loadFromFile("Images/mbg.png");
	tmenubg.setRepeated(true);
	smenubg.setTexture(tmenubg);
	
	for(int i=0;i<5;i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(sf::Color(243,178,52));
		text[i].setCharacterSize(50);
		text[i].setPosition(150, 200+100*i);
	}

	text[0].setString("Play");
	text[0].setFillColor(sf::Color(6,245,245));
	text[0].setCharacterSize(60);
	text[1].setString("Instructions");
	text[2].setString("High Score");
	text[3].setString("About");
	text[4].setString("Exit");
}

void Menu::moveUp()
{
	if(itemIndex>0)
	{
		text[itemIndex].setFillColor(sf::Color(243,178,52));
		text[itemIndex].setCharacterSize(50);
		itemIndex--;
		text[itemIndex].setFillColor(sf::Color(6,245,245));
	}	text[itemIndex].setCharacterSize(60);
}

void Menu::moveDown()
{
	if(itemIndex < 4)
	{
		text[itemIndex].setFillColor(sf::Color(243,178,52));
		text[itemIndex].setCharacterSize(50);
		itemIndex++;
		text[itemIndex].setFillColor(sf::Color(6,245,245));
		text[itemIndex].setCharacterSize(60);
	}
}

void Menu::handleInputs(sf::RenderWindow& app,sf::Event& event,bool& alive, bool& mstate)
{
	if(state)
	{
		if(event.type==sf::Event::KeyPressed)
		{
			if(event.key.code==sf::Keyboard::Down)
			{
				if(app.waitEvent(event))
					moveDown();
			}
		}

		if(event.type==sf::Event::KeyPressed)
		{
			if(event.key.code==sf::Keyboard::Up)
			{
				if(app.waitEvent(event))
					moveUp();
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(app.waitEvent(event))
			{
				if(itemIndex==0)
				{
					alive=true;
					mstate=false;
					//std::cout<<alive<<" "<<mstate<<std::endl;
				}
				if(itemIndex==1)
				{
					Instructions::state=true;
					state=false;
				}
				if(itemIndex==2)
				{
					HighScore::state=true;
					state=false;
				}
				if(itemIndex==3)
				{
					About::state=true;
					state=false;
				}

				if(itemIndex==4)
				{
					exit(0);
				}
			}
		}
	}

	if (Instructions::state)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(app.waitEvent(event))
			{
				Instructions::state=false;
				state=true;
			}
		}
	}
	if(HighScore::state)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(app.waitEvent(event))
			{
				HighScore::state=false;
				state=true;
			}
		}
	}
	if (About::state)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(app.waitEvent(event))
			{
				About::state=false;
				state=true;
			}
		}	
	}
	
}

void Menu::drawMenu(sf::RenderWindow &window)
{
	if(state)
	{
		window.draw(sbgmenu);
		for(int i=0;i<5;i++)
		{
			window.draw(text[i]);
		}
	}
	if(!state)
	{
		window.draw(smenubg);
	}
	if(Instructions::state)
	{
		window.draw(text_instruction);
	}
	if(HighScore::state)
	{
		for(int i=0;i<5;i++)
		{
			window.draw(text_highscore[i]);
		}
	}
	if(About::state)
	{
		window.draw(text_about);
	}
}

#endif

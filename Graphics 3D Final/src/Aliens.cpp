#include "Aliens.h"

std::vector<glm::vec3> Aliens::CreateAliens()
{
	Xpos = -7.5;
	Ypos = 7.0;
	glm::vec3 alien;
	std::vector<glm::vec3> AlienList;
	for (int j = 0; j < 5; j++)
	{
		Xpos = -7.5;
		
		for (int i = 0; i < 11; i++)
		{
			alien.x = Xpos;
			alien.y = Ypos;
			alien.z = 0.0f;
			AlienList.push_back(alien);
			Xpos += 1.5f;

		}
		Ypos -= 1.5f;
	}
	return AlienList;
}

std::vector<glm::vec3> Aliens::AlienMove(std::vector<glm::vec3> AlienList)
{
	glm::vec3 alien;
	
	
	if (FirstCounter == 0)
	{
		moveLeft = false;
	}
	
	if (Timecounter >= Time)
	{
		if (moveLeft == true)
		{
			
			for (int i = 0; i < AlienList.size(); i++)
			{
				
				alien = AlienList.at(i);
				alien.x = alien.x - Speed;
				AlienList.at(i) = alien;
				
				
			}
			if (FirstCounter != 0)
			{
				SpeedCounter = 0;
			}
		}
		else if(moveLeft == false)
		{
			
			for (int i = 0; i < AlienList.size(); i++)
			{
				alien = AlienList.at(i);
				alien.x = alien.x + Speed;
				AlienList.at(i) = alien;
				
			}
			
		}
		Timecounter = 0;
	}
	Timecounter++;
	FirstCounter++;
	SpeedCounter++;
	
	return AlienList;
}

std::vector<glm::vec3> Aliens::MoveDown(std::vector<glm::vec3> AlienList)
{
	glm::vec3 Alien;
	if (Timecounter >= Time)
	{
		if (moveDown == true && NoCounter == 0)
		{
			for (int i = 0; i < AlienList.size(); i++)
			{
				Alien = AlienList.at(i);
				Alien.y = Alien.y - 0.6;
				AlienList.at(i) = Alien;
			}
			Time = Time - 5;
			moveLeft = true;
			moveDown = false;
			NoCounter++;
		}
		if (moveDown == true && NoCounter == 1)
		{
			for (int i = 0; i < AlienList.size(); i++)
			{
				Alien = AlienList.at(i);
				Alien.y = Alien.y - 0.6;
				AlienList.at(i) = Alien;
			}
			Time = Time - 5;
			moveLeft = false;
			moveDown = false;
			NoCounter = 0;
		}
	}
	return AlienList;
}



void Aliens::MoveDownCheck(std::vector<glm::vec3> AlienList)
{
	int winWidth, winHeight;
	SDL_GL_GetDrawableSize(win, &winWidth, &winHeight);
	//half the width for postion of aliens
	winWidth = (winWidth / 2) / 10;
	winWidth -= 1.5;
	float Width = winWidth;
	
	
	
	glm::vec3 Alien;
	int x;
	if(Timecounter>=Time)
	for (int i = 0; i < AlienList.size(); i++)
	{
		Alien = AlienList.at(i);
		x = Alien.x;
		
		if (x == 10.0f)
		{
			moveDown = true;
		}
		else if (x == -10.0f)
		{
			moveDown = true;
		}
		
	}
	
}

void Aliens::GameOverCheck(std::vector<glm::vec3> AlienList,glm::vec3 Player)
{
	glm::vec3 Alien;
	for (int i = 0; i < AlienList.size(); i++)
	{
		Alien = AlienList.at(i);
		if (Alien.y <= Player.y)
		{
			SDL_GL_DeleteContext(win);
			SDL_Quit();
		}
	}
}

void Aliens::AllAliensDestroyed(std::vector<glm::vec3> AlienList)
{
	if (AlienList.size() == 0)
	{
		std::cout << "YOU WIN" << std::endl;
		SDL_GL_DeleteContext(win);
		SDL_Quit();
	}
}




#include "Bullet.h"

glm::vec3  Bullet::createBullet(glm::vec3 PlayerPos)
{
	glm::vec3 Bullet;
	
	
		
		Bullet.x = PlayerPos.x;
		Bullet.y = PlayerPos.y + 0.1;
		Bullet.z = 0.0f;
		
	
	return Bullet;
}

std::vector<glm::vec3> Bullet::createAlienBullet(std::vector<glm::vec3> AlienList, std::vector<glm::vec3> AlienBulletList)
{	
	if (AlienList.size() != 0) 
	{
		int random = rand() % AlienList.size();
		glm::vec3 Bullet;
		glm::vec3 Alien;
		Alien = AlienList.at(random);
		if (TimeDelay >= 80)
		{
			Bullet.x = Alien.x;
			Bullet.y = Alien.y - 0.2;
			TimeDelay = 0;
			AlienBulletList.push_back(Bullet);
		}
		TimeDelay++;
	}
	return AlienBulletList;
}

std::vector<glm::vec3> Bullet::BulletMove(std::vector<glm::vec3> BulletList)
{
	glm::vec3 Bullet;
	for (int i =0; i < BulletList.size(); i++)
	{
		Bullet = BulletList.at(i);
		Bullet.y += 0.07f;
		BulletList.at(i) = Bullet;
	}
	return BulletList;
}

std::vector<glm::vec3> Bullet::AlienBulletMove(std::vector<glm::vec3> AlienBulletList)
{	
	glm::vec3 Alien;
	for (int i = 0; i < AlienBulletList.size(); i++)
	{
		Alien = AlienBulletList.at(i);
		Alien.y -= 0.07f;
		AlienBulletList.at(i)= Alien;
	}
	return AlienBulletList;
}

std::vector<glm::vec3> Bullet::BulletCollision(std::vector<glm::vec3> AlienList)
{	
	
	float y = -7.4f;
	glm::vec3 Alien;
	glm::vec3 bullet;
	float BulletX;
	float BulletY;
	float AlienX;
	float AlienY;
	float AlienLeft;
	float AlienRight;
	float AlienDown;
	float AlienTop;
	//std::cout << BulletList.size();
	for (int i = 0; i < BulletList.size(); i++)
	{
		bool Hit = false;
		bullet = BulletList.at(i);
		BulletX = bullet.x;
		BulletY = bullet.y;
	

		for (int j = 0; j < AlienList.size(); j++)
		{
			Alien = AlienList.at(j);
			AlienX = Alien.x;
			AlienY = Alien.y;
			AlienLeft = Alien.x - 0.75f;
			AlienRight = Alien.x + 0.75f;
			AlienDown = Alien.y - 0.75f;
			AlienTop = Alien.y + 0.75f;
			
			if (BulletX > AlienLeft && BulletX < AlienRight && BulletY<AlienTop && BulletY>AlienDown)
			{
				Hit = true;
				AlienList.erase(AlienList.begin() + j);
				AlienDestroyedList.push_back(glm::vec3(X, y, 0.0f));
				X = X + 0.25f;
				
				break;
			}

			
		}

		if (Hit == true)
		{
			BulletList.erase(BulletList.begin()+i);
		
		}
		
	}
	return AlienList;
}

std::vector<glm::vec3> Bullet::PlrBulletBarricadeCollision(std::vector<glm::vec3> BarricadeList)
{
	glm::vec3 Barricade;
	glm::vec3 Bullet;
	float BarricadeLeft;
	float BarricadeRight;
	float BarricadeTop;
	float BarricadeBottom;
	for (int i = 0; i < BulletList.size(); i++)
	{
		bool Hit = false;
		Bullet = BulletList.at(i);
		
		for (int j = 0; j < BarricadeList.size(); j++)
		{
			Barricade = BarricadeList.at(j);
			BarricadeLeft = Barricade.x - 0.75f;
			BarricadeRight = Barricade.x + 0.75f;
			BarricadeBottom = Barricade.y - 0.75f;
			BarricadeTop = Barricade.y + 0.75f;

			if (Bullet.x > BarricadeLeft && Bullet.x < BarricadeRight && Bullet.y > BarricadeBottom && Bullet.y < BarricadeTop)
			{
				Hit = true;
				BarricadeList.erase(BarricadeList.begin() + j);
			}

		}
		if (Hit == true)
		{
			BulletList.erase(BulletList.begin() + i);
		}
	}
	return BarricadeList;
}

std::vector<glm::vec3> Bullet::EnemyBulletBarricadeCollision(std::vector<glm::vec3> BarricadeList)
{
	glm::vec3 Barricade;
	glm::vec3 Bullet;
	float BarricadeLeft;
	float BarricadeRight;
	float BarricadeTop;
	float BarricadeBottom;
	for (int i = 0; i < AlienBulletList.size(); i++)
	{
		bool Hit = false;
		Bullet = AlienBulletList.at(i);

		for (int j = 0; j < BarricadeList.size(); j++)
		{
			Barricade = BarricadeList.at(j);
			BarricadeLeft = Barricade.x - 0.75f;
			BarricadeRight = Barricade.x + 0.75f;
			BarricadeBottom = Barricade.y - 0.75f;
			BarricadeTop = Barricade.y + 0.75f;

			if (Bullet.x > BarricadeLeft && Bullet.x < BarricadeRight && Bullet.y > BarricadeBottom && Bullet.y < BarricadeTop)
			{
				Hit = true;
				BarricadeList.erase(BarricadeList.begin() + j);
			}

		}
		if (Hit == true)
		{
			AlienBulletList.erase(AlienBulletList.begin() + i);
		}
	}
	return BarricadeList;
}

glm::vec3 Bullet::EnemyBulletCollision(glm::vec3 Player)
{
	glm::vec3 Bullet;
	float PlayerLeft = Player.x -1.0f;
	float PlayerRight = Player.x + 1.0f;
	float PlayerBottom = Player.y - 0.7f;
	float PlayerTop = Player.y +  0.7f;
	

	for (int i = 0; i < AlienBulletList.size(); i++)
	{
		bool hit = false;
		Bullet = AlienBulletList.at(i);
		if (Bullet.x > PlayerLeft && Bullet.x <PlayerRight && Bullet.y>PlayerBottom && Bullet.y < PlayerTop)
		{
			
			if (LivesCounter != 0) {
				AlienBulletList.erase(AlienBulletList.begin() + i);
				LivesList.erase(LivesList.begin() + LivesCounter);
				LivesCounter--;
			}
			else if (LivesCounter == 0)
			{
				std::cout << "GAME OVER" << std::endl;
				SDL_Quit();
			}
			
			
		}

	}
	return Player;
}

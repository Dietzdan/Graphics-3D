#pragma once
//_Bullet
#ifndef BULLET
#define BULLET_H
#include <iostream>
#include <vector>



// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
// #define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern std::vector<glm::vec3> BulletList;
extern std::vector<glm::vec3> AlienBulletList;
extern std::vector<glm::vec3> LivesList;
extern std::vector<glm::vec3> AlienDestroyedList;
class Bullet {
public:
	int LivesCounter = 2;
	int TimeDelay = 0;
	int DestroyedAliens = 0;
	float X = 0.0f;
	
	glm::vec3 createBullet(glm::vec3 PlayerPos);
	std::vector<glm::vec3> createAlienBullet(std::vector<glm::vec3> ALienList, std::vector<glm::vec3> AlienBulletList);
	std::vector<glm::vec3> BulletMove(std::vector<glm::vec3> BulletList);
	std::vector<glm::vec3> AlienBulletMove(std::vector<glm::vec3> AlienBulletList);
	std::vector<glm::vec3> BulletCollision(std::vector<glm::vec3> AlienList);
	std::vector<glm::vec3> PlrBulletBarricadeCollision(std::vector<glm::vec3> BarricadeList);
	std::vector<glm::vec3> EnemyBulletBarricadeCollision(std::vector<glm::vec3> BarricadeList);

	glm::vec3 EnemyBulletCollision(glm::vec3 Player);
};
#endif // !BULLET

#pragma once
//_Aliens
#ifndef ALIENS
#define ALIENS_H
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
extern SDL_Window *win;
class Aliens {
public:
	float Xpos = 0;
	float Ypos = 0;
	float Speed = 0.25f;
	int Time = 50;
	int Timecounter = 0;
	int FirstCounter = 0;
	int SpeedCounter = 0;
	int NoCounter = 0;
	bool moveLeft;
	bool moveDown;
	std::vector<glm::vec3> CreateAliens();
	std::vector<glm::vec3> AlienMove(std::vector<glm::vec3> AlienList);
	std::vector<glm::vec3> MoveDown(std::vector<glm::vec3> AlienList);
	void MoveDownCheck(std::vector<glm::vec3> AlienList);
	void GameOverCheck(std::vector<glm::vec3> AlienList,glm::vec3 Player);
	void AllAliensDestroyed(std::vector<glm::vec3> AlienList);
	

};
#endif // !ALIENS

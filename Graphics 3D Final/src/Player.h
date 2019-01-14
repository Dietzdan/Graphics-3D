#pragma once
//_Player
#ifndef PLAYER
#define PLAYER_H
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
extern std::vector<glm::vec3> LivesList;
class Player {
public:
	float Xpos = -8.3f;
	glm::vec3 CreatePlayer();
	void CreateLives();

};
#endif // !PLAYER

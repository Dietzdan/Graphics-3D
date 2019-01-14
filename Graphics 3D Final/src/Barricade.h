#pragma once
//_Barricade
#ifndef BARRICADE
#define BARRICADE_H
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

class Barricade {
	public:
	int BarricadeCounter = 0;
	std::vector<glm::vec3> CreateBarricades();
	std::vector<glm::vec3> AlienBarricadeCollision(std::vector<glm::vec3> BarricadeList, std::vector<glm::vec3> AlienList);

};
#endif // !BARRICADE


#pragma once
#ifndef MODEL
#define MODEL_H
#include <iostream>
#include <vector>
#include <string>


// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>

// // - OpenGL Mathematics - https://glm.g-truc.net/
// #define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//ASSIMP model loader includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

#include "Mesh.h"

GLint TextureFromFile(const char* path, string directory);

class Model {
public:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> Textures_Loaded;

	Model(GLchar* Path);
	void LoadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	void Draw(GLuint ShaderProgram);
};



#endif // !MODEL

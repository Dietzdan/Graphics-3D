#pragma once
//_Mesh
#ifndef MESH
#define MESH_H
#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<sstream>


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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString Path;
};

class Mesh {
public:
	vector<Vertex> Vertices;
	vector<GLuint> Indices;
	vector<Texture> Textures;
	GLuint VAO, VBO, EBO;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void SetupMesh();
	void Draw(GLuint ShaderProgram);


		

	
	


	


};

#endif // !MESH

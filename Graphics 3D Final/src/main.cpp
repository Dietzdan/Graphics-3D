#include <iostream>
#include <fstream>
#include<sstream>
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
#include "Aliens.h"
#include "Player.h"
#include "Bullet.h"
#include "Barricade.h"
#include "Model.h"
#include "Mesh.h"
//Global Variables
SDL_Window *win;
vector<glm::vec3> BulletList;
vector<glm::vec3> AlienBulletList;
vector<glm::vec3> LivesList;
vector<glm::vec3> AlienDestroyedList;



int main(int argc, char *argv[]) {

	//creating objects 
	Aliens Alien;
	Player Plr;
	Bullet bullet;
	Barricade barricade;
	
	// SDL initialise
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
                    SDL_GetError());
    return 1;
  }
  SDL_Log("SDL initialised OK!\n");

  // SDL_Image initialise
  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_image init error: %s\n",
                    IMG_GetError());
    return 1;
  }
  SDL_Log("SDL_image initialised OK!\n");

  // SDL_ttf initialise
  if (TTF_Init() == -1) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf init error: %s\n",
                    SDL_GetError());
    return 1;
  }
  SDL_Log("SDL_ttf initialised OK!\n");

  // SDL_mixer initialise
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "SDL_mixer init error: %s\n   PERHAPS NO "
                    "HEADPHONES/SPEAKERS CONNECTED\n",
                    Mix_GetError());
    return 1;
  }
  SDL_Log("SDL_mixer initialised OK!\n");
  //creating surfaces to hold textures
  SDL_Surface *AlienTex1;
  SDL_Surface *AlienTex2;
  SDL_Surface *PlayerTex;
  SDL_Surface *WallTex;
  SDL_Surface *BackgroundTex;
  SDL_Surface *BulletTex;
 

  AlienTex1 = IMG_Load("assets/Alien1.png");
  AlienTex2 = IMG_Load("assets/Alien2.png");
  PlayerTex = IMG_Load("assets/Player.png");
  WallTex = IMG_Load("assets/Wall.png");
  BackgroundTex = IMG_Load("assets/Background1.png");
  BulletTex = IMG_Load("assets/Bullet.png");


  //make sure images loaded
  if (!AlienTex1) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", IMG_GetError());
    return 1;
  }
  if (!AlienTex2) {
	  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", IMG_GetError());
	  return 1;
  }
  if (!PlayerTex) {
	  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", IMG_GetError());
	  return 1;
  }
  if (!WallTex) {
	  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", IMG_GetError());
	  return 1;
  }
  if (!BackgroundTex) {
	  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", IMG_GetError());
	  return 1;
  }

 
	  
  

  //Texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  //// Load the font
  //TTF_Font *font = TTF_OpenFont("assets/OpenSans-Bold.ttf", 90);
  //if (font == nullptr) {
  //  SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
  //                  "SDL_ttf font load error: %s\n", SDL_GetError());
  //  return 1;
  //}
  //SDL_Log("SDL_ttf loaded font OK!\n");

  ////// Load the music
  ////Mix_Music *music = Mix_LoadMUS("assets/beat.wav");
  ////if (!music) {
  ////  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS error: %s\n",
  ////              Mix_GetError());
  ////  return 1;
  ////}
  ////SDL_Log("SDL_mixer loaded music OK!\n");

  ////// Load the sound effect
  ////Mix_Chunk *scratch = Mix_LoadWAV("assets/scratch.wav");
  ////if (!scratch) {
  ////  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadWAV error: %s\n",
  ////              Mix_GetError());
  ////  return 1;
  ////}
  ////SDL_Log("SDL_mixer loaded sound effect OK!\n");

 // // Create the font texture
 // SDL_Rect fontRect;
 // SDL_Color fontColor = {255, 0, 0, 255}; // white
 // SDL_Surface *fontSolid = TTF_RenderText_Solid(font, "AwesomeText", fontColor);
 //// SDL_Texture *fontSolidTexture =
 //    // SDL_CreateTextureFromSurface(renderer, fontSolid);
 // //SDL_QueryTexture(fontSolidTexture, NULL, NULL, &fontRect.w, &fontRect.h);
 // fontRect.x = 0;
 // fontRect.y = 0;
 // SDL_Log("SDL_ttf created texture with size %i, %i\n", fontRect.w, fontRect.h);

  // Play the music and sound effect
 /* Mix_PlayChannel(-1, scratch, 0);
  Mix_PlayMusic(music, -1);*/

 


  // Window Creation 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  
  win = SDL_CreateWindow("Daniel Dietzman CGP2012M DIE15561178", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  SDL_GLContext glcontext = SDL_GL_CreateContext(win);
  
  glewExperimental = true;
  if (glewInit()) {
	  std::cout << "Glew ERROR" << std::endl;

  }
  else
  {
	  std::cout << "Glew OK" << std::endl;
  }

  if (win == nullptr) {
	  SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
		  "SDL_CreateWindow init error: %s\n", SDL_GetError());
	  return 1;
  }
  
  //Vertices 
  GLfloat vertices[] = {
	  // Positions          // Texture Coords
	  1.0f, 1.0f, 0.0f,      1.0f, 1.0f, // Top Right
	  1.0f, -1.0f, 0.0f,     1.0f, 0.0f, // Bottom Right
	 -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, // Bottom Left
	 -1.0f, 1.0f, 0.0f,      0.0f, 1.0f // Top Left 
  };
  //Indices
  GLuint indices[] = {
	  0,1,3,
	  1,2,3
  };							
 
  GLfloat AlienData[] = {
		//positions       Textures
	  -1.0, -1.0,  1.0,    0.0f,0.0f, //front  //bottomleft
	   1.0, -1.0,  1.0,    1.0f,0.0f, //bottom right
	   1.0,  1.0,  1.0,    1.0f,1.0f, //top right
	  -1.0,  1.0,  1.0,    0.0f,1.0f, //top left
	  
	   1.0,  1.0,  1.0,   0.0f,0.0f,//right
	   1.0,  1.0, -1.0,	  1.0f,0.0f,
	   1.0, -1.0, -1.0,   1.0f,1.0f,
	   1.0, -1.0,  1.0,   0.0f,1.0f,
	  
	  -1.0, -1.0, -1.0,   0.0f,0.0f,//back
	   1.0, -1.0, -1.0,   1.0f,0.0f,
	   1.0,  1.0, -1.0,   1.0f,1.0f,
	  -1.0,  1.0, -1.0,   0.0f,1.0f,
	  
	  -1.0, -1.0, -1.0,   0.0f,0.0f, //left
	  -1.0, -1.0,  1.0,   1.0f,0.0f,
	  -1.0,  1.0,  1.0,   1.0f,1.0f,
	  -1.0,  1.0, -1.0,   0.0f,1.0f,
	    
	   1.0, 1.0,  1.0,    0.0f,0.0f,//upper 
	  -1.0, 1.0,  1.0,    1.0f,0.0f,
	  -1.0, 1.0, -1.0,    1.0f,1.0f,
	   1.0, 1.0, -1.0,    0.0f,1.0f,
	  
	  -1.0, -1.0, -1.0,   0.0f,0.0f, //bottom
	   1.0, -1.0, -1.0,   1.0f,0.0f,
	   1.0, -1.0,  1.0,   1.0f,1.0f,
	  -1.0, -1.0,  1.0,   0.0f,1.0f

  };

  GLfloat PlayerData[] = {
	  //positions       Textures
	  -2.0, -0.5,  1.0,   0.0f,0.0f,
	  2.0, -0.5,  1.0,   1.0f,0.0f,
	  2.0,  0.5,  1.0,    1.0f,1.0f,
	  -2.0,  0.5,  1.0,      0.0f,1.0f,

	  2.0,  0.5,  1.0,  0.0f,0.0f,
	  2.0,  0.5, -1.0,	 1.0f,0.0f,
	  2.0, -0.5, -1.0,   1.0f,1.0f,
	  2.0, -0.5,  1.0,    0.0f,1.0f,

	  -2.0, -0.5, -1.0,  0.0f,0.0f,
	  2.0, -0.5, -1.0,   1.0f,0.0f,
	  2.0,  0.5, -1.0,    1.0f,1.0f,
	  -2.0,  0.5, -1.0,   0.0f,1.0f,

	  -2.0, -0.5, -1.0,  0.0f,0.0f,
	  -2.0, -0.5,  1.0,   1.0f,0.0f,
	  -2.0,  0.5,  1.0,    1.0f,1.0f,
	  -2.0,  0.5, -1.0,   0.0f,1.0f,

	  2.0, 0.5,  1.0,  0.0f,0.0f,
	  -2.0, 0.5,  1.0,   1.0f,0.0f,
	  -2.0, 0.5, -1.0,    1.0f,1.0f,
	  2.0, 0.5, -1.0,    0.0f,1.0f,

	  -2.0, -0.5, -1.0, 0.0f,0.0f,
	  2.0, -0.5, -1.0,   1.0f,0.0f,
	  2.0, -0.5,  1.0,   1.0f,1.0f,
	  -2.0, -0.5,  1.0,   0.0f,1.0f,

};
  GLfloat BulletData[] = {
	  //positions          //textures
	  -0.5, -1.0, 1.0,  0.0f, 0.0f,
	  0.5, -1.0, 1.0,  1.0f, 0.0f,
	  0.5, 1.0, 1.0,   1.0f, 1.0f,
	  -0.5, 1.0, 1.0,  0.0f, 1.0f,

	  0.5, 1.0, 1.0,   0.0f, 0.0f,
	  0.5, 1.0, -1.0,  1.0f, 0.0f,
	  0.5, -1.0,-1.0,  1.0f, 1.0f,
	  0.5, -1.0, 1.0,  0.0f, 1.0f,

	  -0.5, -1.0, -1.0, 0.0f, 0.0f,
	  0.5, -1.0, -1.0,  1.0f, 0.0f,
	  0.5, 1.0, -1.0,   1.0f, 1.0f,
	  -0.5, 1.0, -1.0,  0.0f, 1.0f,

	 -0.5, -1.0, -1.0,  0.0f, 0.0f,
	 -0.5, -1.0, 1.0,   1.0f, 0.0f,
	 -0.5, 1.0, 1.0,    1.0f, 1.0f,
	 -0.5, 1.0, -1.0,   0.0f, 1.0f,

	  0.5, 1.0, 1.0,    0.0f, 0.0f,
	  -0.5, 1.0, 1.0,   1.0f, 0.0f,
	  -0.5, 1.0, -1.0,  1.0f, 1.0f,
	  0.5, 1.0, -1.0,   0.0f, 1.0f,

	 -0.5, -1.0, -1.0,  0.0f, 0.0f,
	  0.5, -1.0, -1.0,  1.0f, 0.0f,
	  0.5, -1.0, 1.0,   1.0f, 1.0f,
	  -0.5, -1.0, 1.0,  0.0f, 1.0f,
  };






  GLuint CubeIndices[] = {
	  0,  1,  2,  0,  2,  3,   //front
	  4,  5,  6,  4,  6,  7,   //right
	  8,  9,  10, 8,  10, 11,  //back
	  12, 13, 14, 12, 14, 15,  //left
	  16, 17, 18, 16, 18, 19,  //upper
	  20, 21, 22, 20, 22, 23 //bottom
  };
  //vec4(position.x,position.y,position.z,1.0)
  //vertex shader
 /* GLchar const *VertexShader[] = {
	  "#version 450 core\n"
	  "layout(location = 0) in vec3 position;\n"
	  "layout(location = 1) in vec3 normal;\n"
	  "layout(location = 2) in vec2 texCoords;\n"
	  "out vec2 TexCoords;\n"
	  "uniform mat4 modelMat;\n"
	  "uniform mat4 viewMat;\n"
	  "uniform mat4 projectionMat;\n"
	  "void main()\n"
	  "{ gl_Position = projectionMat * viewMat * modelMat * vec4(position.xyz, 1.0);\n"
	  " TexCoords = texCoords;}"
  };*/
  GLchar const *VertexShader[] = {
	  "#version 440 core\n"
	  "layout (location=0) in vec3 position;\n"
	  "layout (location = 1 ) in vec2 texCoord;\n"
	  "out vec2 TexCoord;\n"
	  "uniform mat4 modelMat;\n"
	  "uniform mat4 viewMat;\n"
	  "uniform mat4 projectionMat;\n"
	  "void main()\n"
	  "{ gl_Position = projectionMat * viewMat * modelMat * vec4(position,1.0);\n"
	  " TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);}"
  };
  
  GLchar const *FragmentShader[] = {
	  "#version 440 core\n"
	  "in vec2 TexCoord;\n"
	  "out vec4 color;\n"
	  "uniform sampler2D ourTexture;\n"
	  "void main()\n"
	  "{ vec4 texColor = texture(ourTexture, TexCoord);\n"
	  "color = texColor;}"
  };
 





  
  //compiling Shaders 
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, VertexShader, NULL);
  glCompileShader(vertexShader);
  GLuint fragShader;
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, FragmentShader, NULL);
  glCompileShader(fragShader);
  

  //Shader Progammes
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

  //Use programme delete shaders
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);


  //setting up vertex buffer
  GLuint VBO;
  glGenBuffers(1, &VBO);
  GLuint VBO2;
  GLuint VBO3;
  GLuint VBO4;
  GLuint VBO5;
  glGenBuffers(1, &VBO2);
  glGenBuffers(1, &VBO3);
  glGenBuffers(1, &VBO4);
  glGenBuffers(1, &VBO5);
  //element buffer
  GLuint EBO;
  GLuint EBO2;
  GLuint EBO3;
  GLuint EBO4;
  GLuint EBO5;
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &EBO2);
  glGenBuffers(1, &EBO3);
  glGenBuffers(1, &EBO4);
  glGenBuffers(1, &EBO5);
  //set up textures
  
  GLuint Alien1;
  glGenTextures(1, &Alien1);
  GLuint Alien2;
  glGenTextures(1, &Alien2);
  GLuint Player1;
  glGenTextures(1, &Player1);
  GLuint Barricade1;
  glGenTextures(1, &Barricade1);
  GLuint Background1;
  glGenTextures(1, &Background1);
  GLuint Bullet1;
  glGenTextures(1, &Bullet1);


  //bind Textures
  glBindTexture(GL_TEXTURE_2D, Alien1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AlienTex1->w, AlienTex1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, AlienTex1->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(AlienTex1);

  glBindTexture(GL_TEXTURE_2D, Alien2);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AlienTex2->w, AlienTex2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, AlienTex2->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(AlienTex2);

  glBindTexture(GL_TEXTURE_2D, Player1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PlayerTex->w, PlayerTex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, PlayerTex->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(PlayerTex);

  glBindTexture(GL_TEXTURE_2D, Bullet1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BulletTex->w, BulletTex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, BulletTex->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(BulletTex);

  glBindTexture(GL_TEXTURE_2D, Barricade1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WallTex->w, WallTex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, WallTex->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(WallTex);


  //creating matrixes
  //model vertexes local
  glm::mat4 modelMatrix;
  glm::mat4 rotationMatrix;
  //camera matrix 
  glm::mat4 viewMatrix;
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -20.0f);
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  //points to opposite of target
  glm::vec3 CameraDirection = glm::normalize(cameraPos - cameraTarget); 
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  //points to positive x direction (Switch up and camera around for negative)
  glm::vec3 CameraRight = glm::normalize(glm::cross(up, CameraDirection));
  
  glm::vec3 CameraUp = glm::cross(CameraDirection, CameraRight);
 /* viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
							glm::vec3(0.0f,0.0f,0.0f),
							glm::vec3(0.0f,0.5f,0.0f));*/
  
  
  //Projection matrix for othro or perspective 
  glm::mat4 projectionMatrix;
  int height, width;

  SDL_GetWindowSize(win, &width, &height);
  //othro projection
  //projectionMatrix = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, -1.0f, 100.f);
  //perspective projection
  projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
// translate model to middle of the screen 
 
  glm::vec3 alien;
  glm::vec3 Lives;
  glm::vec3 player;
  glm::vec3 Bullet;
  glm::vec3 Barricades;
  glm::vec3 DestroyedAliens;
  
  std::vector<glm::vec3> alienList = Alien.CreateAliens();
  std::vector<glm::vec3> BarricadeList = barricade.CreateBarricades();
  Plr.CreateLives();
  player = Plr.CreatePlayer();

 
  //Initialization of VAO
  GLuint VAO;
  GLuint VAO2;
  GLuint VAO3;
  GLuint VAO4;
  GLuint VAO5;
  glGenVertexArrays(1, &VAO);
  glGenVertexArrays(1, &VAO2);
  glGenVertexArrays(1, &VAO3);
  glGenVertexArrays(1, &VAO4);
  glGenVertexArrays(1, &VAO5);
  //Aliens data 
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(AlienData), AlienData, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);
  
 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
 
  
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  //player data
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);

  glBufferData(GL_ARRAY_BUFFER, sizeof(PlayerData), PlayerData, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);


  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
  
  //Bullet
  glBindVertexArray(VAO3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO3);

  glBufferData(GL_ARRAY_BUFFER, sizeof(BulletData), BulletData, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);


  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  glBindVertexArray(VAO4);
  glBindBuffer(GL_ARRAY_BUFFER, VBO4);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);


  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);



 
  glEnable(GL_DEPTH_TEST);
  glBindVertexArray(0);

  glm::vec3 AlienView = alienList.at(38);



  

  
  GLint projectionLocation = glGetUniformLocation(shaderProgram, "projectionMat");
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  GLint ViewLocation = glGetUniformLocation(shaderProgram, "viewMat"); //TODO expensive, cache the value
  GLuint modelLocation = glGetUniformLocation(shaderProgram, "modelMat");
  viewMatrix = glm::translate(viewMatrix, cameraPos); //camera is invert of this
  SDL_Event Works;
  glm::vec3 normalView = glm::vec3(0.0f, 0.0f, -20.0f);
  int TimeDelay = 0;
  int AnimationTime = 0;
  bool running = true;
  bool FullScreen = false;
  bool FreeCam = false;
  int cameracounter = 0;
  double StartTime = SDL_GetTicks();
  while (running)
  { 
	 

	  if (cameracounter == 0)
	  {

		  viewMatrix = glm::mat4();
		  cameraPos = normalView;
		  viewMatrix = glm::translate(viewMatrix, cameraPos);//camera is invert of this
		  
      }
	  if (cameracounter == 1)
	  {
		  cameraPos = glm::vec3(0.0f, 18.0f, -5.0f);
		  viewMatrix = glm::lookAt(cameraPos, player, glm::vec3(0.0f, 1.0f, 0.0f));
	  }
	  if (cameracounter == 2)
	  {
		  cameraPos = glm::vec3(18.0f, 9.0f, -8.0f);
		  viewMatrix = glm::lookAt(cameraPos, player, glm::vec3(0.0f, 1.0f, 0.0f));
	  }
	  if (cameracounter == 3)
	  {
		  cameraPos = glm::vec3(0.0f, -20.0f, -5.0f);
		  
		  viewMatrix = glm::lookAt(cameraPos, glm::normalize(cameraPos - player), glm::vec3(0.0f, 1.0f, 0.0f));
	  }
	  
	  Alien.AllAliensDestroyed(alienList);
	  TimeDelay++;
	  AnimationTime++;

	  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	
	  glUseProgram(shaderProgram);
	  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	
	 

	 //player bullet
	  glBindTexture(GL_TEXTURE_2D, Bullet1);
	  glBindVertexArray(VAO3);
	  for (int i = 0; i < BulletList.size(); i++)
	  {
		  modelMatrix = glm::mat4();
		  Bullet = BulletList.at(i);
		  
		  modelMatrix = glm::translate(modelMatrix, Bullet);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.3f, 0.3f));
		  
		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	  }
	 //alienbullet

	  for (int i = 0; i < AlienBulletList.size(); i++)
	  {
		  modelMatrix = glm::mat4();
		  Bullet = AlienBulletList.at(i);

		  modelMatrix = glm::translate(modelMatrix, Bullet);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.3f, 0.3f));

		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



	  }

	  glBindVertexArray(0);
	  
	  //aliens
	  modelMatrix = glm::mat4();
	  if (AnimationTime < 50)
	  {
		  glBindTexture(GL_TEXTURE_2D, Alien2);
	  }
	  if (AnimationTime > 50)
	  {
		  glBindTexture(GL_TEXTURE_2D, Alien1);
	  }
	  if (AnimationTime >= 100)
	  {
		  AnimationTime = 0;
	  }
	  glBindVertexArray(VAO);
	  for (int num = 0; num < alienList.size(); num++)
	  {		
		  alien = alienList.at(num);
		  modelMatrix = glm::mat4();
		  modelMatrix = glm::translate(modelMatrix, alien);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
		  modelLocation = glGetUniformLocation(shaderProgram, "modelMat");
		  ViewLocation = glGetUniformLocation(shaderProgram, "viewMat");

		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		
	  }
	  
	 
	  //Barricade
	  glBindTexture(GL_TEXTURE_2D, Barricade1);
	  glBindVertexArray(VAO);
	  for (int i = 0; i < BarricadeList.size(); i++)
	  {
		  Barricades = BarricadeList.at(i);

		  modelMatrix = glm::mat4();
		  modelMatrix = glm::translate(modelMatrix, Barricades);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 0.4f, 0.4f));

		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));


		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	  }
	


	  //score 
	  glBindVertexArray(VAO4);
	  glBindTexture(GL_TEXTURE_2D, Alien1);
	  for (int i = 0; i < AlienDestroyedList.size(); i++)
	  {
		  DestroyedAliens = AlienDestroyedList.at(i);
		  modelMatrix = glm::mat4();
		  modelMatrix = glm::translate(modelMatrix, DestroyedAliens);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 0.4f, 0.4f));

		  modelLocation = glGetUniformLocation(shaderProgram, "modelMat");
		  ViewLocation = glGetUniformLocation(shaderProgram, "viewMat");

		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	  }
	  //player
	  glBindTexture(GL_TEXTURE_2D,Player1);
	  glBindVertexArray(VAO2);
	  
	  modelMatrix = glm::mat4();
	  modelMatrix = glm::translate(modelMatrix, player);
	  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	  
	  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	  
	  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	  //Lives
	  for (int i = 0; i < LivesList.size(); i++)
	  {
		  modelMatrix = glm::mat4();
		  Lives = LivesList.at(i);
		  
		  modelMatrix = glm::translate(modelMatrix, Lives);
		  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 0.4f, 0.4f));

		  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		  glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	  }
	  glBindVertexArray(0);

	 
	 
	  SDL_GL_SwapWindow(win);

	  if (FreeCam == false)
	  {
		  alienList = Alien.AlienMove(alienList);
		  Alien.MoveDownCheck(alienList);
		  alienList = Alien.MoveDown(alienList);
		  AlienBulletList = bullet.createAlienBullet(alienList, AlienBulletList);
		  AlienBulletList = bullet.AlienBulletMove(AlienBulletList);
		  BulletList = bullet.BulletMove(BulletList);
		  alienList = bullet.BulletCollision(alienList);
		  player = bullet.EnemyBulletCollision(player);
		  BarricadeList = bullet.PlrBulletBarricadeCollision(BarricadeList);
		  BarricadeList = bullet.EnemyBulletBarricadeCollision(BarricadeList);
		  BarricadeList = barricade.AlienBarricadeCollision(BarricadeList, alienList);
		  Alien.GameOverCheck(alienList, player);
	  }

	  while (SDL_PollEvent(&Works) != 0)
	  {
		  if (Works.type == SDL_QUIT)
		  {
			  SDL_DestroyWindow(win);

			  running = false;
		  }
		  if (Works.type == SDL_KEYDOWN)
		  {

			  switch (Works.key.keysym.sym)
			  {
			  case SDLK_ESCAPE:
				  SDL_DestroyWindow(win);
				  running = false;
				  break;
			  case SDLK_a:
				   player.x -= 0.15f;
				  break;
			  case SDLK_d:
				  player.x += 0.15f;
				  break;
			  case SDLK_SPACE:
				  
				  if (TimeDelay >= 30)
				  {
					  BulletList.push_back(bullet.createBullet(player));
					  TimeDelay = 0;
				  }
				  break;
			  case SDLK_RETURN:
				  if (FullScreen == false)
				  {
					  SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
					  FullScreen = true;
				  }
				  else if (FullScreen == true)
				  {
					  SDL_SetWindowFullscreen(win, 0);
					  FullScreen = false;
				  }
				  break;
			  case SDLK_c:
				  if (FreeCam == false)
				  {
					  FreeCam = true;
				  }
				  else if (FreeCam == true)
				  {
					  FreeCam = false;
					  normalView =  glm::vec3(0.0f,0.0f,-20.0f);
					  cameraPos = normalView;
				  }
				  break;
			  case SDLK_LEFT:
				  if (FreeCam == true)
				  {
					  normalView.x += 0.1f;
					  
				  }
				  break;
			  case SDLK_RIGHT:
				  if (FreeCam == true)
				  {
					  normalView.x -= 0.1f;
					 
				  }
				  break;
			  case SDLK_UP:
				  if (FreeCam == true)
				  {
					  normalView.y -= 0.1f;
					 
				  }
				  break;
			  case SDLK_DOWN:
				  if (FreeCam == true)
				  {
					  normalView.y += 0.1f;
					  
				  }
				  break;
			  case SDLK_z:
				  if (FreeCam == true)
				  {
					  normalView.z += 0.1f;
					  
				  }
				  break;
			  case SDLK_x:
				  if (FreeCam == true)
				  {
					  normalView .z-= 0.1f;
					  
				  }
				  break;
			  case SDLK_g:
				  cameracounter++;
				  if (cameracounter == 4)
				  {
					  cameracounter = 0;
				  }
					  break;
			  }
		  }
	  }

	 

  }

 // Clean up
  SDL_Log("Finished. Cleaning up and closing down\n");

 // Mix_FreeChunk(scratch);
 // Mix_FreeMusic(music);
 // Mix_CloseAudio();

 //// SDL_DestroyTexture(fontSolidTexture);
 //// SDL_FreeSurface(fontSolid);

 //// SDL_DestroyTexture(logoTexture);
 // SDL_FreeSurface(logoSurface);
  SDL_GL_DeleteContext(win);
  SDL_Quit();
  return 0;
}

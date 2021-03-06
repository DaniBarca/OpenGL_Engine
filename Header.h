#pragma once

/*OpenGL*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>

/*Assimp (for 3D model load)*/
#pragma comment(lib, "assimp-vc130-mt.lib") 

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

/*C++*/
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;
using namespace std::placeholders;

/***************/
/* DEFINITIONS */
/***************/

#define fscanf fscanf_s

typedef unsigned int uint;

//Directions
/*enum DIRECTION {
	FRONT = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BACK,
	N_DIRECTIONS
} DIRECTION;

glm::mat4x4 TURN[6] = {
	glm::mat4(),
	glm::rotate(90.0f, glm::vec3(0,0,1)),
	glm::rotate(-90.0f,glm::vec3(0,0,1)),
	glm::rotate(-90.0f,glm::vec3(0,1,0)),
	glm::rotate(90.0f, glm::vec3(0,1,0)),
	glm::rotate(180.0f,glm::vec3(0,1,0))
};*/

//Screen size
constexpr uint SCREEN_WIDTH = 1024;
constexpr uint SCREEN_HEIGHT = 768;

//Inverse screen size (better performance for some operations)
//Could mean a difference if you use this data intensively
constexpr double I_SCREEN_WIDTH  = 1.0 / ((double)SCREEN_WIDTH);
constexpr double I_SCREEN_HEIGHT = 1.0 / ((double)SCREEN_HEIGHT);

//Number of vertices of a polygon and dimensions
constexpr uint VERTICES_PER_POL = 3;
constexpr uint DIMENSIONS = 3;			//Which is obvious but I don't like magic numbers
constexpr uint N_AXIS = 3;

//Default number of lights
constexpr uint DEFAULT_N_POINT_LIGHTS = 3;
constexpr uint DEFAULT_N_SPOT_LIGHTS = 3;
constexpr uint DEFAULT_N_DIRECTIONAL_LIGHTS = 3;

//Standard vector value for each direction
#define V_UP   glm::vec3(0,1,0)
#define V_DOWN glm::vec3(0,-1,0)

#define V_RIGHT glm::vec3(1,0,0)
#define V_LEFT  glm::vec3(-1,0,0)

#define V_FRONT glm::vec3(0,0,1)
#define V_BACK  glm::vec3(0,0,-1)

//Mathematical constants and usual operations
constexpr double PI	     = 3.14159265358979323846f;
constexpr double TAU     = 2*PI;
constexpr double DEG2RAD = 0.01745329251994329576923f;
constexpr double RAD2DEG = 57.2957795130823208767981f;

constexpr float I_256 = 1.0f / 256.0f;

constexpr double DEGTORAD(double d) { return d*DEG2RAD; };
constexpr double RADTODEG(double r) { return r*RAD2DEG; };

constexpr float DEGTORAD(float d) { return d*(float)DEG2RAD; };
constexpr float RADTODEG(float r) { return r*(float)RAD2DEG; };

glm::mat4 getRotationMatrix(double radians, glm::vec3 axis);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
glm::vec4 clamp(glm::vec4 v);

/* Engine options */
//#define PRINT_FPS

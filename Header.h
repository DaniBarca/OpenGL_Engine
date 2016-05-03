#pragma once

/*OpenGL*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

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

/*own defines*/
constexpr int VERTICES_PER_POL = 3;

constexpr double PI	     = 3.14159265358979323846f;
constexpr double TAU     = 2*PI;
constexpr double DEG2RAD = 0.01745329251994329576923f;
constexpr double RAD2DEG = 57.2957795130823208767981f;

constexpr double DEGTORAD(double d) { return d*DEG2RAD; };
constexpr double RADTODEG(double r) { return r*RAD2DEG; };

constexpr float DEGTORAD(float d) { return d*(float)DEG2RAD; };
constexpr float RADTODEG(float r) { return r*(float)RAD2DEG; };

glm::mat4 getRotationMatrix(double radians, glm::vec3 axis);

using namespace std;
using namespace std::placeholders;

/* Engine options */
//#define PRINT_FPS

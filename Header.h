#pragma once

/*OpenGL*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
#define VERTICES_PER_POL 3

#define PI      3.14159265358979323846f
#define TAU		2*PI
#define DEG2RAD 0.01745329251994329576923f
#define RAD2DEG 57.2957795130823208767981f

#define DEGTORAD(d) d*DEG2RAD
#define RADTODEG(r) r*RAD2DEG

glm::mat4 getRotationMatrix(double radians, glm::vec3 axis);

using namespace std;

void voxelParse(string path, vector<vector<vector<int>>>* voxels, int* width, int* height, int* depth);
void printVoxels(vector<vector<vector<int>>> voxels, int width, int height, int depth);

typedef enum {
	LEFT,
	RIGHT
}DIRECTION;

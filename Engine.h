#pragma once
#include "Header.h"

/*OpenGL*/
//#include <glm\gtc\matrix_transform.hpp>

#ifndef UP
#define UP glm::vec3(0,1,0)
#endif

class Engine
{
	static Engine* Instance;
	
	GLFWwindow* window;

	Engine();
	~Engine();

	static void reshape(GLFWwindow* window, int width, int height);

	function<void(int,int,int,int)> OnKeyPress;
	function<void(int, int, int)> OnMousePress;
	function<void(double, double)> OnMouseMove;

	static void Key(GLFWwindow* window, int k, int s, int action, int mods);
	static void MPress(GLFWwindow* window, int b, int a, int m);
	static void MMove(GLFWwindow* window, double x, double y);

public:
	static Engine* GetInstance();
	Engine* InitGLFW();
	Engine* NewWindow(int width, int height, string title, function<void(int, int, int, int)> OnKeyPress, function<void(int,int,int)> OnMousePress, function<void(double,double)> OnMouseMove);
	Engine* InitGLEW();
	Engine* InitEngine();
	Engine* Loop(function<void()>Init, function<void(double)> Update, function<void()> Draw);
	Engine* Terminate();

	Engine* LoadShader(string vertex_path, string fragment_path, GLuint* out_shader_id);
};
